# http://csrc.nist.gov/publications/fips/fips197/fips-197.pdf
import constants_aes as constants
from calculatorGF256 import multicationGF, sumGF

def sub_bytes(state):

    char_to_bits = [bin(each_vector_element|256)[3:] for each_vector_element in state]

    index_of_sub_bytes = [(int(bytes_string[0:4],2),int(bytes_string[4:8],2)) for bytes_string in char_to_bits]

    index_vector_from_matrix = [constants.s_box[index[0]*16+index[1]] for index in index_of_sub_bytes]

    print (index_vector_from_matrix)
    return index_vector_from_matrix

def invert_state(state):
    block_invert = [0 for x in state]
    for i in range(len(state)):
        row = int(i/4)
        column = (i%4)
        block_invert[column*4+row] = state[row*4+column]

    print(block_invert)
    return block_invert

def shift_rows(pre_state):
    state = invert_state(pre_state)

    row_one = 4
    row_two = 8
    row_three = 12

    state = [state[0], state[1], state[2], state[3],
            state[row_one+1], state[row_one+2], state[row_one+3], state[row_one],
            state[row_two+2], state[row_two+3],state[row_two],state[row_two+1],
            state[row_three+3],state[row_three],state[row_three+1],state[row_three+2]]

    print(invert_state(state))
    return state

def mix_columns(state):
    mix_result = [0 for x in state]

    for row in range(4):
        for column in range(4):
            for i in range(4):
                mix_result[column+4*row] = sumGF(mix_result[column+4*row],multicationGF(constants.table_mix_columns[row*4+i]
                                                                                        ,state[column+4*i]))

    return mix_result

def function_g(block_word, round_index):
    #Circular shift
    block_word.append(block_word[0])
    block_word.pop(0)

    block_word = sub_bytes(block_word)

    block_word[0] = constants.rcj[round_index]^block_word[0]

    return block_word

def expansion_key(key):

    #Copy list
    expanded_key = key[:]
    for round_index in range(10):
        for j in range(4):
            w=expanded_key[-4:]
            if j==0:
                w=function_g(w,round_index)
            expanded_key.extend(x[0]^x[1] for x in zip(w,expanded_key[-16:-12]))

    return expanded_key

def add_round_key():
    return ""

def cipher_aes():
    # state_after_sub_bytes = sub_bytes([0x00,0x10,0x20,0x30,0x40,0x50,0x60,0x70,0x80,0x90,0xa0,0xb0,0xc0,0xd0,0xe0,0xf0])
    state_after_sub_bytes = sub_bytes([0x0f,0x15,0x71,0xc9,0x47,0xd9,0xe8,0x59,0x0c,0xb7,0xad,0xd6,0xaf,0x7f,0x67,0x98])
    state_after_shift_rows = shift_rows(state_after_sub_bytes)
    state_after_mix_columns = mix_columns(state_after_shift_rows)
   # expansion_key([0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f])
    expansion_key([0x0f,0x15,0x71,0xc9,0x47,0xd9,0xe8,0x59,0x0c,0xb7,0xad,0xd6,0xaf,0x7f,0x67,0x98])
    print(state_after_mix_columns)
        #add_round_key()

if __name__ == "__main__" :
    cipher_aes()

