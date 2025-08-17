def main():
   
   matrix = [[0 for x in range(8)] for x in range(6)]
   
   for i in range(6):
      for j in range(8):
         if (j != 1):
            matrix[i][j] = [0, 0]
         else:
            matrix[i][j] = [i+1, j+1]
      print(matrix[i])
   print("\n")
   
   for i in range(6):
      for j in range(8):
         if (j == 4):
            matrix[i][j] = matrix[i][1]
      print(matrix[i])
   print("\n")
   

if __name__ == "__main__":
   main()

