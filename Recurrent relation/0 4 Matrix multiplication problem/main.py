from numpy import zeros
fin = open("input.txt")
fout = open("output.txt", "w")
n = int(fin.readline())
vals = []
for i in range(0, n-1):
    vals.append(int(fin.readline().split()[0]))
vals+=[int(i) for i in fin.readline().split()]
mult = zeros((n,n),dtype=int)
for len in range(2, n+1):
    for i in range(0, n-len+1):
        mult[i][i+len-1]=min([mult[i][i+m] + mult[i+m+1][i+len-1] +vals[i]*vals[i+m+1]*vals[i+len-1+1] for m in range(len-1)])
fout.write(str(mult[0][n-1]))