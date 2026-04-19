# Extract 

import json
import numpy as np
import os



def load_iterations(filepath):
    with open(filepath, 'r') as f:
        data = json.load(f)

    iterations = data["results"]["iteration_counts"]
    avg = sum(iterations) / len(iterations)

    problem = data.get("problem", os.path.basename(filepath))

    print(problem, end='\t')
    print(avg)



if __name__ == "__main__":
    def process_folder(folder_path):
        for root, dirs, files in os.walk(folder_path):
            for filename in files:
                full_path = os.path.join(root, filename)
                load_iterations(full_path)
    
    process_folder("shared_results/AS/small")
    process_folder("shared_results/AS/medium")
    process_folder("shared_results/AS/large")
    process_folder("shared_results/MA/small")
    process_folder("shared_results/MA/medium")
    process_folder("shared_results/MA/large")
