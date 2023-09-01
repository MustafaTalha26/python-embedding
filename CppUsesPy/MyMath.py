class SimpleMath: 
    def multiply(first,second):
        c = int(first*second)
        print ('The result of', first, 'x', second, ':', c)
        return c
    
    def divide(first,second):
        c = int(first/second)
        print ('The result of', first, '/', second, ':', c)
        return c
    
    def sumup(array):
        sum = 0
        for num in array:
            sum += num
        print ('The sum of numbers are :', sum)
        return sum
    
    def trystruct(array):
        print ('The dictionary is :', array, '\n')
        return array;