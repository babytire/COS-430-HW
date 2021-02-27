#Ryan Handlon
#COS 430
#S-AES Program
#Due: 2/27/21

plaintext = 0b0110111101101011          #Put plaintext in binary here
key = 0b1010011100111011                #Put key in binary here
encrypted = 0b0000000000000000          

#sbox values: index = input, element = output
sbox = [0b1001, 0b0100, 0b1010, 0b1011, 0b1101, 0b0001, 0b1000, 0b0101, 0b0110, 0b0010, 0b0000, 0b0011, 0b1100, 0b1110, 0b1111, 0b0111]
#galios field table multipules of four: index = input, element = output
galios_fileld_table_4 = [0x00, 0x04, 0x08, 0x0c, 0x03, 0x07, 0x0b, 0x0f, 0x06, 0x02, 0x0e, 0x0a, 0x05, 0x01, 0x0d, 0x09]

#subkey calculation
w0 = (key & 0b1111111100000000) >> 8
w1 = key & 0b0000000011111111
w2 = w0 ^ 0b10000000 ^ ((sbox[w1 & 0b00001111] << 4) | (sbox[w1 >> 4]))
w3 = w1 ^ w2
w4 = w2 ^ 0b00110000 ^ ((sbox[w3 & 0b00001111] << 4) | (sbox[w3 >> 4]))
w5  = w3 ^ w4

key0 = (w0 << 8) | w1
key1 = (w2 << 8) | w3
key2 = (w4 << 8) | w5

#xor with key0
encrypted = plaintext ^ key0 
#nibble substitution
encrypted = (sbox[(encrypted & 0b1111000000000000) >> 12] << 12) | (sbox[(encrypted & 0b0000111100000000) >> 8] << 8) | (sbox[(encrypted & 0b0000000011110000) >> 4] << 4) | sbox[encrypted & 0b0000000000001111]
#nibble swap
encrypted = (encrypted & 0b1111000011110000) | ((encrypted & 0b0000111100000000) >> 8) | ((encrypted & 0b0000000000001111) << 8)  
#Mix columns
a = (((encrypted & 0b1111000000000000) >> 12) ^ galios_fileld_table_4[(encrypted & 0b0000111100000000) >> 8]) << 12
b = (galios_fileld_table_4[(encrypted & 0b1111000000000000) >> 12] ^ ((encrypted & 0b0000111100000000) >> 8)) << 8
c = (((encrypted & 0b0000000011110000) >> 4) ^ galios_fileld_table_4[(encrypted & 0b0000000000001111)]) << 4
d = (galios_fileld_table_4[(encrypted & 0b0000000011110000) >> 4] ^ (encrypted & 0b0000000000001111))
encrypted = a | b | c | d
#xor with key1
encrypted = encrypted ^ key1
#nibble substitution
encrypted = (sbox[(encrypted & 0b1111000000000000) >> 12] << 12) | (sbox[(encrypted & 0b0000111100000000) >> 8] << 8) | (sbox[(encrypted & 0b0000000011110000) >> 4] << 4) | sbox[encrypted & 0b0000000000001111]
#nibble swap
encrypted = (encrypted & 0b1111000011110000) | ((encrypted & 0b0000111100000000) >> 8) | ((encrypted & 0b0000000000001111) << 8)
#xor with key2
encrypted = encrypted ^ key2

print ( "Your plaintext in binary was: " + (bin(plaintext)))
print ("Your key in binary was: " + (bin(key)))
print ("Your plaintext encrypted with your key is: " + (bin(encrypted)))
