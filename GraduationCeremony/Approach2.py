'''

# considering 3 days each as one set. so possible outcomes for 3 days are 8 = ["AAA","AAP",'APA','APP','PAA','PAP','PPA','PPP']

# for each set XP => no of possibilities having last day as Present =>4= ["AAP","APP","PAP","PPP"]
# for each set XA => no of possibilities having only last day as Absent => 2 =["APA","PPA"]
# for each set XAA => no of possibilities having last 2 days as Absent => 1 =["PAA"]
# for each set AAA => no of possibilities having last 3 days as Absent => 1 = ["AAA"]

#splitting all the given no of days into 3 days as one set
for no 0f days as 6 : no of sets of 6 => 6/3 = 2sets
for 1 set 1 (3 days):

XP = 4
XA = 2
XAA = 1
AAA = 1

above metrics will keep on updating for every iteration

possible ways for   6 days =  function(3days, 3days) => 1st(iteration)
                    9 days = function(function(3days, 3days),3days) =>  2nd iteration
                    12 days = function(function(function(3days, 3days),3days), 3days) => 3rd iteration
                    .
                    .
                    .
                    n days = function(function(n-3days,3days), 3days) => n//3 iteration
updation will be as follows:

current set 
                  
XP = 4  
XA = 2
XAA = 1
AAA = 1  

formuala for updation of XP : e = XP * 4 + XA * 4 + XAA * 3 + AAA * 2

checking all combinations in  set 1 (XP,XA,XAA,AAA)  againt XP .  so it can combine with all the possible ways
            that student can Present on last day in second set (XP) to give last day as present)
            like (XPXP,XAXP,XAAXP,AAAXP)
            
updated_XP1 = XP * 4["AAP","APP","PAP","PPP"] => (XP represent student present on last day in set 1.  so it can combine 
                       with all the possible ways that student can Present on last day in second set to give last day as present)
                       4 denotes no of possibles ways student can present on last day in second set 
updated_Xp2 = XA * 4["AAP","APP","PAP","PPP"] =>  (XA represent student Absent on last day in set 1.  so it can combine 
                       with all the possible ways that student can Present on last day in second set to give last day as present) 
updated_Xp3 = XAA * 3["APP","PAP","PPP"]   => (XAA represent student Absent on last 2 day in set 1.  so it can combine 
                       with all the possible ways that student can Present on last day in second set to give last day as present)
                        only 3 out of 4 ["AAP","APP","PAP","PPP"] are valid.  "AAP" is invalid as XAA alread had 2 days as end when combined
                        AAAAP +=> 4 as consecutive days 
    
updated_XP4 = AAA * 2 ["PAP","PPP"]  => only 2 out of 4 possiblities ["AAP","APP","PAP","PPP"] are valid.  "AAP","APP" Are invalid  as they result in AAAAAP,AAAAAP


so UpdatedXP = updated_XP1 + updated_Xp2 + updated_Xp3 + updated_Xp4
             = (XP * 4) + (XA * 4) + (XAA * 3)  + (AAA * 2) 
similary for others too

after n//3 iterations:


no of possible ways for attending classes = (XP + XA + XAA + AAA)
no of ways missing ceremony = XA + XAA + AAA

space complexity : O(1)
time complexity : O(n//3)
'''




N = int(input())    
iterations = N // 3
XP = 4  # present at last day
XA = 2 # Absent at Last day
XAA = 1 # Absent for last 2 days
AAA = 1 # Absent for last 3 days
for k in range(iterations - 1):
    e = XP * 4 + XA * 4 + XAA * 3 + AAA * 2
    f = XP * 2 + XA * 2 + XAA * 2 + AAA * 1
    g = XP + XA + XAA + AAA
    h = XP * 1
    XP, XA = e, f
    XAA, AAA = g, h
if (N % 3 == 2):
    e = XP * 2 + XA * 2 + XAA * 2 + AAA * 1
    f = XP + XA + XAA + AAA
    g = XP
    h = XA
    XP, XA = e, f
    XAA, AAA = g, h
elif (N % 3 == 1):
    e = XP + XA + XAA + AAA
    f = XP
    g = XA
    h = XAA
    XP, XA = e, f
    XAA, AAA = g, h

totalWays = XP + XA + XAA + AAA
missingCeremonyWays = XA + XAA + AAA
print(str(missingCeremonyWays) + "/" + str(totalWays))
