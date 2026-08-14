#include <iostream>
using namespace std;

int main() {
    int a, b, c, d;
    int subnets;

    cout << "Enter IP address: ";
    cin >> a >> b >> c >> d;

    // Validate IP
    if (a < 1 || a > 223 ||
        b < 0 || b > 255 ||
        c < 0 || c > 255 ||
        d < 0 || d > 255) {
        cout << "Invalid IP Address";
        return 0;
    }

    cout << "Enter required number of subnets: ";
    cin >> subnets;

    if (subnets <= 0) {
        cout << "Invalid number of subnets";
        return 0;
    }

    int defaultBits;
    int hostBits;

    // Find class
    if (a >= 1 && a <= 126) {
        cout << "\nClass A" << endl;
        defaultBits = 8;
        hostBits = 24;
    }
    else if (a >= 128 && a <= 191) {
        cout << "\nClass B" << endl;
        defaultBits = 16;
        hostBits = 16;
    }
    else if (a >= 192 && a <= 223) {
        cout << "\nClass C" << endl;
        defaultBits = 24;
        hostBits = 8;
    }
    else {
        cout << "Subnetting allowed only for Class A, B or C";
        return 0;
    }

    // Find borrowed bits
    int borrowedBits = 0;
    int numberOfSubnets = 1;

    while (numberOfSubnets < subnets) {
        borrowedBits++;
        numberOfSubnets = numberOfSubnets * 2;
    }

    // Check available bits
    if (borrowedBits >= hostBits) {
        cout << "Cannot create required number of subnets";
        return 0;
    }

    int newBits = defaultBits + borrowedBits;
    int remainingBits = 32 - newBits;

    int totalAddresses = 1;

    for (int i = 0; i < remainingBits; i++) {
        totalAddresses = totalAddresses * 2;
    }

    int usableHosts = totalAddresses - 2;

    cout << "\nSUBNET CALCULATION" << endl;
    cout << "Default Prefix: /" << defaultBits << endl;

    if (defaultBits == 8)
        cout << "Default Mask: 255.0.0.0" << endl;
    else if (defaultBits == 16)
        cout << "Default Mask: 255.255.0.0" << endl;
    else
        cout << "Default Mask: 255.255.255.0" << endl;

    cout << "Borrowed Bits: " << borrowedBits << endl;
    cout << "New Prefix: /" << newBits << endl;
    cout << "Total Subnets: " << numberOfSubnets << endl;
    cout << "Remaining Host Bits: " << remainingBits << endl;
    cout << "Addresses per Subnet: " << totalAddresses << endl;
    cout << "Usable Hosts per Subnet: " << usableHosts << endl;

    // Find subnet mask
    int mask1 = 0;
    int mask2 = 0;
    int mask3 = 0;
    int mask4 = 0;

    if (newBits <= 8) {
        int bits = newBits;

        for (int i = 0; i < bits; i++)
            mask1 = mask1 + (1 << (7 - i));
    }
    else if (newBits <= 16) {
        mask1 = 255;
        int bits = newBits - 8;

        for (int i = 0; i < bits; i++)
            mask2 = mask2 + (1 << (7 - i));
    }
    else if (newBits <= 24) {
        mask1 = 255;
        mask2 = 255;
        int bits = newBits - 16;

        for (int i = 0; i < bits; i++)
            mask3 = mask3 + (1 << (7 - i));
    }
    else {
        mask1 = 255;
        mask2 = 255;
        mask3 = 255;
        int bits = newBits - 24;

        for (int i = 0; i < bits; i++)
            mask4 = mask4 + (1 << (7 - i));
    }

    cout << "New Subnet Mask: "
         << mask1 << "."
         << mask2 << "."
         << mask3 << "."
         << mask4 << endl;

    // Classful network address
    int networkA = a;
    int networkB = b;
    int networkC = c;
    int networkD = d;

    if (defaultBits == 8) {
        networkB = 0;
        networkC = 0;
        networkD = 0;
    }
    else if (defaultBits == 16) {
        networkC = 0;
        networkD = 0;
    }
    else {
        networkD = 0;
    }

    cout << "\nClassful Network Address: "
         << networkA << "."
         << networkB << "."
         << networkC << "."
         << networkD << endl;

    // Subnet increment
    int blockSize;

    if (newBits <= 8)
        blockSize = 256 / (mask1 + 1);
    else if (newBits <= 16)
        blockSize = 256 / (mask2 + 1);
    else if (newBits <= 24)
        blockSize = 256 / (mask3 + 1);
    else
        blockSize = 256 / (mask4 + 1);

    cout << "Subnet Increment: " << blockSize << endl;

    // Display subnets
    cout << "\nSUBNET DETAILS" << endl;

    for (int i = 0; i < numberOfSubnets; i++) {

        int na = networkA;
        int nb = networkB;
        int nc = networkC;
        int nd = networkD;

        // Class A
        if (defaultBits == 8) {
            nb = i * blockSize;
        }

        // Class B
        else if (defaultBits == 16) {
            nc = i * blockSize;
        }

        // Class C
        else {
            nd = i * blockSize;
        }

        cout << "\nSubnet " << i + 1 << endl;

        cout << "Network Address: "
             << na << "." << nb << "."
             << nc << "." << nd << endl;

        // First and last usable host
        int fa = na;
        int fb = nb;
        int fc = nc;
        int fd = nd + 1;

        int la = na;
        int lb = nb;
        int lc = nc;
        int ld = nd + blockSize - 2;

        // Class A
        if (defaultBits == 8) {
            fb = nb;
            fc = 0;
            fd = 1;

            lb = nb;
            lc = 255;
            ld = 254;
        }

        // Class B
        else if (defaultBits == 16) {
            fc = nc;
            fd = 1;

            lc = nc;
            ld = 254;
        }

        cout << "First Usable Host: "
             << fa << "." << fb << "."
             << fc << "." << fd << endl;

        cout << "Last Usable Host: "
             << la << "." << lb << "."
             << lc << "." << ld << endl;

        // Broadcast address
        int ba = na;
        int bb = nb;
        int bc = nc;
        int bd = nd;

        // Class A
        if (defaultBits == 8) {
            bb = nb + blockSize - 1;
            bc = 255;
            bd = 255;
        }

        // Class B
        else if (defaultBits == 16) {
            bc = nc + blockSize - 1;
            bd = 255;
        }

        // Class C
        else {
            bd = nd + blockSize - 1;
        }

        cout << "Broadcast Address: "
             << ba << "." << bb << "."
             << bc << "." << bd << endl;

        cout << "Subnet Mask: "
             << mask1 << "." << mask2 << "."
             << mask3 << "." << mask4 << endl;

        cout << "CIDR: /" << newBits << endl;
    }

    return 0;
}