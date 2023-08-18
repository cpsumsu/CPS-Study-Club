def dynamicProgramming(x, m, y, n):
    # Initialize the scoring matrix
    T = [[0 for j in range(n+1)] for i in range(m+1)]
    for j in range(1, n+1):
        T[0][j] = T[0][j-1] + Ins(y[j-1])
    for i in range(1, m+1):
        T[i][0] = T[i-1][0] + Del(x[i-1])
    
    # Fill in the rest of the scoring matrix using dynamic programming
    for i in range(1, m+1):
        for j in range(1, n+1):
            sub_cost = Sub(x[i-1], y[j-1])
            T[i][j] = min(T[i-1][j-1] + sub_cost, T[i-1][j] + Del(x[i-1]), T[i][j-1] + Ins(y[j-1]))
    
    # Trace back through the scoring matrix to find the optimal alignment
    alignment_x = ""
    alignment_y = ""
    i = m
    j = n
    while i > 0 or j > 0:
        if i > 0 and j > 0 and T[i][j] == T[i-1][j-1] + Sub(x[i-1], y[j-1]):
            alignment_x = x[i-1] + alignment_x
            alignment_y = y[j-1] + alignment_y
            i -= 1
            j -= 1
        elif i > 0 and T[i][j] == T[i-1][j] + Del(x[i-1]):
            alignment_x = x[i-1] + alignment_x
            alignment_y = "-" + alignment_y
            i -= 1
        else:
            alignment_x = "-" + alignment_x
            alignment_y = y[j-1] + alignment_y
            j -= 1

    # Output the optimal alignment and the minimum cost
    print("The cost is:", T[m][n])
    print("A possible alignment is:")
    print(alignment_x)
    print("|" * len(alignment_x))
    print(alignment_y)
    

# Define the cost functions
def Sub(a, b):
    if a == b:
        return 0
    else:
        return 2

def Del(a):
    return 1

def Ins(a):
    return 1


# Test the implementation
x = "AACGCA"
y = "GAGCTA"
dynamicProgramming(x, len(x), y, len(y))
