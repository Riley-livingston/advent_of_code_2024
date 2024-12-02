def calculate_total_distance(left_list, right_list):
    """
    Calculate the total distance between two lists of numbers.
    Each number in the left list is paired with a number in the right list
    after both lists are sorted, and the absolute differences are summed.
    """
    # Sort both lists
    left_sorted = sorted(left_list)
    right_sorted = sorted(right_list)
    
    # Make sure the lists are the same length
    if len(left_sorted) != len(right_sorted):
        raise ValueError("Lists must be of equal length")
    
    # Calculate the total distance
    total_distance = 0
    for left_num, right_num in zip(left_sorted, right_sorted):
        distance = abs(left_num - right_num)
        total_distance += distance
        
    return total_distance



def calculate_similarity_score(left_list, right_list):
    """
    Calculate the similarity score between two lists.
    For each number in the left list, multiply it by the number of times
    it appears in the right list and sum all these products.
    """
    # Count occurrences in the right list
    right_counts = {}
    for num in right_list:
        right_counts[num] = right_counts.get(num, 0) + 1
    
    # Calculate similarity score
    total_score = 0
    for num in left_list:
        # Multiply the number by its frequency in the right list (0 if not present)
        frequency = right_counts.get(num, 0)
        score = num * frequency
        total_score += score
    
    return total_score



def parse_input_file(filename):
    """
    Read and parse input from a txt file into two lists of numbers.
    """
    left_list = []
    right_list = []
    
    try:
        with open(filename, 'r') as file:
            for line in file:
                # Skip empty lines
                if not line.strip():
                    continue
                
                # Split the line by whitespace and convert to integers
                numbers = [int(n) for n in line.split()]
                if len(numbers) != 2:
                    raise ValueError(f"Invalid input line: {line}")
                
                left_list.append(numbers[0])
                right_list.append(numbers[1])
                
    except FileNotFoundError:
        print(f"Error: File '{filename}' not found")
        return None, None
    except ValueError as e:
        print(f"Error parsing file: {e}")
        return None, None
        
    return left_list, right_list




# Read input from file in day_1 folder
file_path = 'input.txt'
left_list, right_list = parse_input_file(file_path)

if left_list is not None and right_list is not None:
    # Calculate part 1 (distance)
    distance = calculate_total_distance(left_list, right_list)
    print(f"Part 1 - Total distance: {distance}")

    # Calculate part 2 (similarity score)
    similarity = calculate_similarity_score(left_list, right_list)
    print(f"Part 2 - Similarity score: {similarity}")