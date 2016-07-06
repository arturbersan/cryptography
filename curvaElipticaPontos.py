def extend_euclids(a,b):
    if b>a: 
        a,b = b,a
    r = [a,b] 
    s = [1,0] # alpha value
    t = [0,1] # beta value
    
    while(r[0]%r[1] != 0):
        rt = r[0]%r[1] 
        q = int(r[0]/r[1])
        
        st =  s[0] - s[1]*q # calculate the new value of alpha
        tt = t[0] - t[1]*q # calculate the new value of beta
        
        r[0]=r[1]
        r[1]=rt
        s[0]=s[1]
        s[1]=st # update the value of alpha
        t[0]=t[1]
        t[1]=tt # update the value of beta
    
    inverse_multiplicative = (r[1],t[1])
    return inverse_multiplicative

def validate_input(a,b,p):
    """ Verify if a and b satisfy the equation
        4a^3 + 27b^2 ( mod p ) != 0
        true if satisfy
        false if not
    """
    first_term = 4*(a**3) % p
    second_term = 27*(b**2) % p
    result = ( first_term + second_term ) % p

    return result != 0

def find_all_points(a,b,p):
    """A brute force to find all points in eclipse curve cryptografy
       over prime Zp: y^2 = x^3 + Ax + b
    """
    value_xy=[] # contains values of y when positive, where (x,y) £ E(p)
    for x in range(0,p):
        for y in range(0,p):
            auxY = (y**2)%p
            auxX = ((x**3)%p + (a*x %p) + b)%p
            if auxY == auxX:
                value_xy.append((x,y))
    return value_xy

def find_lambda(x,y,a):
    lambdaP = ( (3*(x**2)) +a)/(2*y)
    print(lambdaP)
    return lambdaP

def find_order_of_point(x,y,a,p):
    order=1
    lambdaP = find_lambda(x,y,a)
    pointXr = ((lambdaP**2) - 2*x)%p
    pointYr = (lambdaP*(x-pointXr)-y)%p

    while pointXr != x and pointYr != y:
        pointXr = ((lambdaP**2) - 2*x)%p
        pointYr = (lambdaP*(x-pointXr)-y)%p
        order +=1

    return order

def find_order_of_array(array,a,p):
    list_order=[]
    for point in array:
        list_order.append(find_order_of_point(point[0],point[1],a,p))

    return list_order

if __name__ == "__main__":
    a = int(input("A value\n"))
    b = int(input("B value\n"))
    p = int(input("P value\n"))

    if validate_input(a,b,p):
        print("Valid valor of inputs 'a' and 'b'\nPoint of curve: ")
        value_xy = find_all_points(a,b,p)
        list_order = find_order_of_array(value_xy,a,p)
        print(value_xy)
        print("Total number of point:")
        print(len(value_xy))
        print("Order of point:")
        print(list_order)

    else:
        print("invalid A and B") 
