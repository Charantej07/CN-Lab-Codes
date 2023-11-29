def get_ip_class(ip_address):
    octets = ip_address.split('.')
    first_octet = int(octets[0])
    if 1 <= first_octet <= 126:
        return "Class A"
    elif 128 <= first_octet <= 191:
        return "Class B"
    elif 192 <= first_octet <= 223:
        return "Class C"
    elif 224 <= first_octet <= 239:
        return "Class D"
    elif 240 <= first_octet <= 255:
        return "Class E"
    else:
        return "Invalid IP address"


def generate_subnet_ip(ip_address, subnet_bits):
    octets = ip_address.split('.')
    subnet_mask = 0xFFFFFFFF << (32 - subnet_bits)
    octets[0] = str(int(octets[0]) & (subnet_mask >> 24 & 0xFF))
    octets[1] = str(int(octets[1]) & (subnet_mask >> 16 & 0xFF))
    octets[2] = str(int(octets[2]) & (subnet_mask >> 8 & 0xFF))
    octets[3] = str(int(octets[3]) & (subnet_mask & 0xFF))
    return '.'.join(octets)


if __name__ == "__main__":
    ip_address = input("Enter the IP address: ")
    subnet_bits = int(input("Enter the number of subnet bits: "))
    ip_class = get_ip_class(ip_address)
    subnet_ip = generate_subnet_ip(ip_address, subnet_bits)
    print("IP Class:", ip_class)
    print("Subnet IP:", subnet_ip)
