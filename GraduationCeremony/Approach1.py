

'''
Approach 1

counting all the valid possible outcomes while generating possible ways in recursion and at each step of generation
checking the case of isConsecutiveAbsentCaseFailed

time complexity : O(2^n)
space complexity : O(n)

'''
class GraduationUtil:
 def __init__(self):
     self.totalCount = 0
     self.MissinglastDayCount = 0
    
 def getCounts(self):
     return (self.totalCount, self.MissinglastDayCount)
    
 def isConsecutiveAbsentCaseFailed(self,temp):
     AbsentForFourConsecutiveDays = ['A']*4
     if(temp[-4:] == AbsentForFourConsecutiveDays):
         return True
        

 def generate(self,n):
     
     def generatePermutations(temp,i):
         # checking if last 4 days are absent if yes trunctating the recursive call 
         if(len(temp)>=4 and temp[-1]=='A' and self.isConsecutiveAbsentCaseFailed(temp)==True):
             return
         # when possible way obtained for n days  counting it as totalCount(total number of posssible ways to attend
         # the college. count the MissingLastDayCount when the obtained temp string contains last day as Absent => 'A'
         if(i==n):
             
             self.totalCount = self.totalCount + 1
             if(temp[-1]=='A'):
                 self.MissinglastDayCount = self.MissinglastDayCount + 1
             return
         # considering Absent for current Day
         temp.append('A')
         generatePermutations(temp,i+1)
         # backtracking 
         temp.pop(-1)
         # considering Present for current Day
         temp.append('P')
         generatePermutations(temp,i+1)
         # backtracking
         temp.pop(-1)
     return generatePermutations([],0)


x = int(input())
grad = GraduationUtil()
grad.generate(x)
counts = grad.getCounts()
print("".join([str(counts[1]),"/",str(counts[0])]))
