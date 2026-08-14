#include <iostream>
using namespace std;

int main() {
    int data[20] = {0};
    int hamming[31] = {0};
    int received[31] = {0};

    int m;

    cout << "Enter number of data bits: ";
    cin >> m;

    cout << "Enter the data bits from LEFT to RIGHT:\n";
    for (int i = 0; i < m; i++) {
        cin >> data[i];
    }

    cout << "Input Data = ";
    for (int i = 0; i < m; i++) {
        cout << data[i];
    }
    cout << endl;

    int r = 0;

    while ((1 << r) < (m + r + 1)) {
        r++;
    }

    int n = m + r;

    cout << "\nSTEP 1: Calculate Parity Bits\n";
    cout << "Number of data bits   = " << m << endl;
    cout << "Number of parity bits = " << r << endl;
    cout << "Total number of bits  = " << n << endl;

    for (int i = 1; i <= n; i++) {
        hamming[i] = 0;
    }

    cout << "\nSTEP 2: Place Data Bits\n";

    int dataIndex = 0;

    for (int i = n; i >= 1; i--) {
        if ((i & (i - 1)) != 0) {
            hamming[i] = data[dataIndex];
            dataIndex++;
        }
    }

    cout << "\nPosition: ";
    for (int i = n; i >= 1; i--) {
        cout << i << " ";
    }

    cout << "\nBit:      ";
    for (int i = n; i >= 1; i--) {
        if ((i & (i - 1)) == 0)
            cout << "P ";
        else
            cout << hamming[i] << " ";
    }

    cout << "\n";

    cout << "\nSTEP 3: Calculate Parity Bits\n";

    for (int p = 0; p < r; p++) {
        int parityPosition = 1 << p;
        int parity = 0;

        cout << "\nP" << parityPosition << " checks positions: ";

        for (int i = 1; i <= n; i++) {
            if (i & parityPosition) {
                cout << i << " ";

                if (i != parityPosition) {
                    parity = parity ^ hamming[i];
                }
            }
        }

        hamming[parityPosition] = parity;

        cout << "\nP" << parityPosition
             << " = " << hamming[parityPosition] << endl;
    }

    cout << "\nSTEP 4: Generated Hamming Code\n";

    cout << "Position: ";
    for (int i = n; i >= 1; i--) {
        cout << i << " ";
    }

    cout << "\nBit:      ";
    for (int i = n; i >= 1; i--) {
        cout << hamming[i] << " ";
    }

    cout << "\nHamming Code = ";

    for (int i = n; i >= 1; i--) {
        cout << hamming[i];
    }

    cout << endl;

    int errorPosition;

    cout << "\nSTEP 5: Error Introduction\n";
    cout << "Enter position to introduce error (0 for no error): ";
    cin >> errorPosition;

    for (int i = 1; i <= n; i++) {
        received[i] = hamming[i];
    }

    if (errorPosition != 0) {
        received[errorPosition] = 1 - received[errorPosition];
        cout << "Error introduced at position "
             << errorPosition << endl;
    } else {
        cout << "No error introduced.\n";
    }

    cout << "Received Code = ";

    for (int i = n; i >= 1; i--) {
        cout << received[i];
    }

    cout << endl;

    cout << "\nSTEP 6: Error Detection\n";

    int error = 0;

    for (int p = 0; p < r; p++) {
        int parityPosition = 1 << p;
        int parity = 0;

        cout << "\nChecking P" << parityPosition << ": ";

        for (int i = 1; i <= n; i++) {
            if (i & parityPosition) {
                cout << i << " ";
                parity = parity ^ received[i];
            }
        }

        cout << "\nXOR result = " << parity;

        if (parity == 1) {
            cout << " -> Error in this parity group\n";
            error = error + parityPosition;
        } else {
            cout << " -> No error in this parity group\n";
        }
    }

    cout << "\nSTEP 7: Error Result\n";

    if (error == 0) {
        cout << "No error detected!\n";
    } else {
        cout << "Error detected at position: " << error << endl;

        received[error] = 1 - received[error];

        cout << "Error corrected successfully.\n";

        cout << "Corrected Hamming Code = ";

        for (int i = n; i >= 1; i--) {
            cout << received[i];
        }

        cout << endl;
    }

    cout << "\nSTEP 8: Extract Data Bits\n";

    cout << "Data Bits = ";

    for (int i = n; i >= 1; i--) {
        if ((i & (i - 1)) != 0) {
            cout << received[i];
        }
    }

    cout << endl;

    return 0;
}