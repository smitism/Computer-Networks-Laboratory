# IP Address Class Calculator
# Classful Addressing

# Function to calculate IP address details
def ip_details(broadcast):

    # Print basic networking definitions
    print("""
========== BASIC DEFINITIONS ==========

Subnet:
A subnet is a smaller part of a network created by dividing a large network.

Subnet Mask:
A subnet mask separates the network part and host part of an IP address.

Loopback Address:
An IP address used by a computer to communicate with itself.

Loopback Range:
127.0.0.0 - 127.255.255.255

Uses:
- Testing TCP/IP
- Troubleshooting network problems
- Checking network configuration

Common Loopback Address:
127.0.0.1 = localhost
""")

    # Split the IP address into four octets
    octets = broadcast.split(".")

    # Check if exactly four octets are present
    if len(octets) != 4:
        print("Invalid IP Address")
        return

    try:
        # Convert the first octet into an integer
        first_octet = int(octets[0])
    except:
        # If conversion fails, the IP address is invalid
        print("Invalid IP Address")
        return

    # Check whether the IP belongs to the Loopback range
    if first_octet == 127:
        print("""
========== RESULT ==========

This is a Loopback Address.

Reason:
127.0.0.0 - 127.255.255.255 is reserved
for loopback testing and is not assigned
to normal hosts.
""")
        return

    # Determine the class of the IP address
    if 1 <= first_octet <= 126:
        ip_class = "Class A"
        subnet_mask = "255.0.0.0"
        network_bits = 7
        host_bits = 24

    elif 128 <= first_octet <= 191:
        ip_class = "Class B"
        subnet_mask = "255.255.0.0"
        network_bits = 14
        host_bits = 16

    elif 192 <= first_octet <= 223:
        ip_class = "Class C"
        subnet_mask = "255.255.255.0"
        network_bits = 21
        host_bits = 8

    elif 224 <= first_octet <= 239:
        # Class D is used for multicast communication
        print("""
Class D Address

Used for multicast communication.
""")
        return

    elif 240 <= first_octet <= 255:
        # Class E is reserved for experimental purposes
        print("""
Class E Address

Reserved for experimental purposes.
""")
        return

    else:
        # Any value outside valid range is invalid
        print("Invalid IP Address")
        return

    # Calculate the number of possible networks
    if ip_class == "Class A":
        network_formula = "2^7 - 2"
        networks = (2 ** 7) - 2
        network_calculation = """
2^7 - 2
= 128 - 2
= 126
"""
    else:
        network_formula = f"2^{network_bits}"
        networks = 2 ** network_bits
        network_calculation = f"""
{network_formula}
= {networks}
"""

    # Calculate the number of usable host addresses
    host_formula = f"2^{host_bits} - 2"
    total_addresses = 2 ** host_bits
    users = total_addresses - 2

    # Display IP information
    print("""
========== IP INFORMATION ==========
""")

    print("Broadcast Address :", broadcast)
    print("Class             :", ip_class)
    print("Subnet Mask       :", subnet_mask)

    # Display network calculation
    print("""
========== NETWORK CALCULATION ==========
""")

    print("Formula:")
    print("Number of Networks =", network_formula)
    print("Calculation:")
    print(network_calculation)
    print("Number of Networks =", networks)

    # Display host calculation
    print("""
========== HOST CALCULATION ==========
""")

    print("Formula:")
    print("Number of Hosts = 2^(Host Bits) - 2")
    print("Host Bits =", host_bits)
    print("\nCalculation:")
    print(host_formula)
    print("=", total_addresses, "- 2")
    print("=", users)

    print("""
Why -2 is used:

Two IP addresses are reserved:

1. Network Address:
   Identifies the network.

2. Broadcast Address:
   Sends data to all devices in the network.

Therefore:

Usable Hosts = 2^(Host Bits) - 2
""")

# Main Program

# Take broadcast address input from the user
broadcast_address = input("Enter Broadcast Address: ")

# Call the function to display IP details
ip_details(broadcast_address)