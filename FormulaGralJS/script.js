'use strict';

const button = document.getElementById('homeButton');
const navButtons = document.querySelectorAll('.nav_element');
const [...inputFields] = document.querySelectorAll('.input__field');
const answers1 = document.getElementById('answers1');
const answers2 = document.getElementById('answers2');
const resultsLabel = document.querySelector('.results__label');
const okButton = document.getElementById('ok');
const [...descriptions] = document.querySelectorAll('.method__description');
const modal = document.querySelector('.modal');
const overlay = document.querySelector('.overlay');
const closeButton = document.getElementById('modalButton');

document.addEventListener('keydown', function (e) {
  if (e.key === 'Escape' && !modal.classList.contains('hidden')) {
    modal.classList.add('hidden');
    overlay.classList.add('hidden');
  }
});

class Equation {
  _mode;
  constructor([a, b, c], mode) {
    this.a = +a;
    this.b = +b;
    this.c = +c;
    this._mode = mode;
    this._modeController();
  }
  _showResults(x1, x2) {
    console.log('hey hey', x1, x2);
    resultsLabel.classList.remove('hidden');
    answers1.textContent = `x1:  ${-x1}`;
    answers2.textContent = `x2: ${-x2}`;
  }

  _insideRad() {
    return Math.sqrt(Math.pow(this.b, 2) - 4 * this.a * this.c);
  }

  _generalFormula() {
    console.log('FG');
    const start = Date.now();
    const x1 = (-(-this.b + this._insideRad()) / 2) * this.a;
    const x2 = (-(-this.b - this._insideRad()) / 2) * this.a;
    const end = Date.now();
    console.log(start - end);
    this._showResults(x1, x2);
  }

  _bruteForce() {
    console.log('BF');
    const start = new Date().getTime();

    for (let i = 0; i < 10000; i++) {
      for (let j = 0; j < 10000; j++) {
        if (!this._checkNumbers(i, j)) {
          continue;
        } else {
          const [x1, x2] = this._checkNumbers(i, j);
          const end = new Date().getTime();
          console.log(end - start);
          this._showResults(x1, x2);
          return false;
        }
      }
    }
    // this._showResults('Not Found', 'not Found');
  }

  _randomNumbers = async function () {
    console.log('RN');
    let found = false;
    let x1;
    let x2;
    const start = new Date().getTime();
    while (!found) {
      x1 = Math.trunc(Math.random() * 1000) + 1;
      x2 = Math.trunc(Math.random() * 1000) + 1;
      // console.log('x1', x1, 'x2', x2);
      if (this._checkNumbers(x1, x2)) {
        const [one, two] = this._checkNumbers(x1, x2);
        console.log(one, two);
        const end = new Date().getTime();
        console.log((end - start) / 1000);
        this._showResults(one, two);
        found = true;
      }
    }

    this._showResults();
  };

  _checkNumbers(i, j) {
    if (i + j === this.b && i * j === this.c) {
      return [i, j];
    }
    if (-i + j === this.b && -i * j === this.c) {
      return [-i, j];
    }
    if (i - j === this.b && i * -j === this.c) {
      return [i, -j];
    }
    if (-i - j === this.b && -i * -j === this.c) {
      return [-i, -j];
    }
    return false;
  }
  _modeController() {
    if (this._mode === '#formula_general') this._generalFormula();

    if (this._mode === '#fuerza_bruta') this._bruteForce();

    if (this._mode === '#numeros_aleatorios') this._randomNumbers();
  }
}

class App {
  _currentMode = '#formula_general';
  constructor() {
    //Event listeners
    navButtons.forEach((nv) =>
      nv.addEventListener('click', this._showMethod.bind(this))
    );
    okButton.addEventListener('click', this._validateData.bind(this));
    closeButton.addEventListener('click', this._closeModal);
    overlay.addEventListener('click', this._closeModal);
    button.addEventListener('click', () => {
      location.replace('./index.html');
    });
  }

  _showMethod(el) {
    //hacer que se oculten los que no sean iguales a este ID ->
    const target = `${el.target.dataset.id}`;
    descriptions.forEach((desc) => desc.classList.add('hidden'));
    document
      .getElementById(`${el.target.dataset.id}`)
      .classList.remove('hidden');
    this._currentMode = target;
    resultsLabel.classList.add('hidden');
  }

  _validateData() {
    const values = [];
    inputFields.forEach((fld) => {
      values.push(fld.value.trim());
    });
    console.log(2, values);

    if (!values.every((val) => Number.isFinite(Number(val)) && val !== '')) {
      this._showModal('Todos los campos deben tener un número entero');
    } else if (values[0] == 0) {
      this._showModal(
        'Si el valor a es igual a 0, entonces no es una fórmula cuadrática'
      );
    } else if (Math.pow(values[1], 2) - 4 * values[0] * values[2] < 0) {
      this._showModal(
        'La ecuación no tiene solución en el campo de los reales'
      );
    } else {
      new Equation(values, this._currentMode);
    }
  }
  _closeModal() {
    console.log('hiding');
    modal.classList.add('hidden');
    overlay.classList.add('hidden');
  }

  _showModal(err) {
    modal.children[1].textContent = err;
    modal.classList.remove('hidden');
    overlay.classList.remove('hidden');
  }
}

const app = new App();
