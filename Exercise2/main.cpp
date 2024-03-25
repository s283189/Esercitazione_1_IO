#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

// Funzione per mappare i punti nell'intervallo [-1, 2]
double mapValue(double value)
{
    return -1 + (value - 1) * (3. / 4.);
}

int main()
{
    string inputFileName = "data.csv";
    string outputFileName = "result.csv";

    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);

    if (inputFile.fail())
    {
        cerr << "Errore nell'apertura del file di input." << endl;
        return 1;
    }

    if (outputFile.fail())
    {
        cerr << "Errore nell'apertura del file di output." << endl;
        return 1;
    }

    double value;
    double sum = 0;
    int N = 0;

    // Lettura dei valori dal file
    cout << "Valori dal file " << inputFileName << ":" << endl;
    while (inputFile >> value)
    {
        cout << value << setprecision(17) << endl;
    }

    // Chiudo il file di input e riapro per tornare all'inizio
    inputFile.close();
    inputFile.open(inputFileName);

    outputFile << "# N Mean" << endl;

    // Leggo i valori dal file di input e calcolo la media
    while (inputFile >> value)
    {
        sum += mapValue(value);
        ++N;
        double mean = sum / N;
        // Scrivo i risultati nel file result con 16 cifre significative
        outputFile << N << " " << fixed << setprecision(16) << mean << endl;
    }

    cout << "Il risultato e' stato scritto nel file " << outputFileName << endl;

    // Chiudo i file
    inputFile.close();
    outputFile.close();

    // Lettura e stampa del file di risultato
    ifstream resultFile(outputFileName);
    if (resultFile.fail())
    {
        cerr << "Errore nell'apertura del file di risultato." << endl;
        return 1;
    }

    cout << "Contenuto di " << outputFileName << ":" << endl;
    string line;
    while (getline(resultFile, line))
    {
        cout << line << endl;
    }

    // Chiudo il file di risultato
    resultFile.close();

    return 0;
}
