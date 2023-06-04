//Generate a system of linear equations with n variables and m simultaneous equations
//randomly. The system must be solvable.

namespace GeneradorSE
{
    class GeneradorSE
    {
        static Random rnd = new Random();
        static void Generate(int numberOfEquations)
        {
            //String para imprimir el número de variables y ecuaciones
            String text = "";
            //Variable auxiliar para generar los coeficientes de las ecuaciones
            int coefficient = 0;
            //Variable para enderezar el resultado
            int constant = 0;

            int[] numberOfVariablesArray = { 5, 10, 20 };

            foreach (int numberOfVariables in numberOfVariablesArray)
            {
                //Matriz con las soluciones del sistema
                int[] arrayOfSolutiosn = new int[numberOfVariables];
                //Ciclo para generar todos los sistemas de ecuaciones
                for (int i = 0; i < numberOfEquations; i++)
                {
                    text += numberOfVariables.ToString() + "\n";
                    //Colocar valores random a las soluciones (números de -15 a 15)
                    for (int j = 0; j < numberOfVariables; j++)
                    {
                        arrayOfSolutiosn[j] = rnd.Next(1, 10);
                    }
                    //Creando matriz con el formato indicado
                    for (int j = 0; j < numberOfVariables; j++)
                    {
                        constant = 0;
                        //Creando el sistema de ecuaciones
                        foreach (int solution in arrayOfSolutiosn)
                        {
                            coefficient = rnd.Next(1, 11);
                            //ternario para colocar el signo al coeficiente
                            coefficient = rnd.Next(0, 2) == 0 ? coefficient : -coefficient;
                            text += coefficient.ToString() + " ";
                            constant += coefficient * solution;
                        }
                        text += constant.ToString() + " ";
                    }
                    text += "\n";
                }
            }

            String path = "C:\\Users\\memoo\\Documents\\Git\\ProgramacionCientifica\\sistemas.txt";
            File.WriteAllText(path, text);
        }
        static void Main(string[] args)
        {
            Generate(5);
        }
    }
}