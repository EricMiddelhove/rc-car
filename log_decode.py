import os
import sys

def main():

  args = sys.argv[1:]

  filepath = args[0]

  if not os.path.exists(filepath):
    print('File does not exist')
    sys.exit(1)
  
  
  
  csv_data = "xAcc, yAcc, zAcc, xGyro, yGyro, zGyro, steeringPercent, acceleratorPercent, coures, targetCourse\n"

  with open(filepath, 'rb') as open_file: 
    
    numbercount = 0

    while (bytes := open_file.read(2)):
        number = int.from_bytes(bytes,"big",signed=True)
        
        csv_data += str(number)
        numbercount += 1

        if numbercount % 10 == 0:
            csv_data += "\n"
        else:
            csv_data += ","
  
  with open("output.csv", "w") as output_file:
    output_file.write(csv_data)




if __name__ == '__main__':
    main()