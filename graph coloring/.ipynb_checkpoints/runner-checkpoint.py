import sys

from subprocess import call

def work(file):
    #print("python main function")
    cmd = "deterministic_solver"
    #file_name = str(sys.argv).split()[1][1:-2]
    file_name = file
    call(["make", cmd]) # compilation
    output = call(["./" + cmd, file_name])

    f = open("output.txt", "r")
    data = f.read()
    return data
    
def prepare(file):
    data = work(file)
    items = data.split("\n")[2:-1]
    colors = []
    for line in items:
        value = int(line.split()[-1])
        colors.append(value)
    return colors

def get_max_clique(file):
    #print("python main function")
    cmd = "max_clique"
    #file_name = str(sys.argv).split()[1][1:-2]
    file_name = file
    call(["make", cmd]) # compilation
    output = call(["./" + cmd, file_name])

    f = open("clique_output.txt", "r")
    data = f.read()
    lines = data.split("\n")
    return int(lines[0].split()[-1])

def bound_quantum_chromatic_number(file):
    coloring = prepare(file)
    clique = get_max_clique(file)
    return clique, max(coloring) + 1