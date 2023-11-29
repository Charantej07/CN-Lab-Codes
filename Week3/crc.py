msg = input("Enter the data: ")
divisor = input("Enter the divisor: ")
divisor_len = len(divisor)
dividend = list(msg+'0'*(divisor_len-1))
for i in range(len(msg)):
    if dividend[i] == "1":
        for j in range(divisor_len):
            dividend[i+j] = str(int(dividend[i+j])+int(divisor[j]))
crc = "".join(dividend[-(divisor_len-1):])
print(msg+crc)
