import os

def process_data(input_data):
    input_lines = input_data.strip().split('\n')
    
    try:
        n = int(input_lines[0])  # Number of arrays
    except ValueError as e:
        print(f"Error while parsing the number of arrays: {e}")
        return "Error in input format"
    
    arrays = []
    index = 1
    
    while index < len(input_lines):
        try:
            k = int(input_lines[index])  # Number of elements in the current array
            
            # Convert all elements in the next line to integers
            arr = list(map(int, input_lines[index + 1].strip().split()))
            
            if len(arr) != k:
                raise ValueError("Number of elements does not match the specified count")
            
            arrays.append(arr)
            index += 2
        except ValueError as e:
            print(f"Error while parsing array data: {e}")
            return "Error in input format"
    
    outputs = []
    for arr in arrays:
        if not arr:
            outputs.append("0")
            continue
        
        max_elem = max(arr)
        result = [0] * (max_elem + 1)
        for num in arr:
            result[num] += 1
        outputs.append(" ".join(map(str, result)))
    
    return "\n".join(outputs)

def process_files_in_directory(directory):
    for folder in range(1, 6):
        folder_path = os.path.join(directory, f"{folder:02d}")
        input_file_path = os.path.join(folder_path, "input")
        output_file_path = os.path.join(folder_path, "output")

        if os.path.exists(input_file_path):
            with open(input_file_path, 'r') as input_file:
                input_data = input_file.read()
                output_data = process_data(input_data)
                
                with open(output_file_path, 'w') as output_file:
                    output_file.write(output_data)
                print(f"Processed {input_file_path} and wrote output to {output_file_path}")
        else:
            print(f"Input file {input_file_path} does not exist.")

if __name__ == "__main__":
    directory = "/home/dragon/Git/C_lag/CAS/test_data"
    process_files_in_directory(directory)
