# Convert the .csv file to an h file, ready to be built.

INPUT_FILENAME = "./board_data.csv"
OUTPUT_FILENAME = "../board_data.h"

VAR_TYPE = "static unsigned char"
VAR_NAME = "board_idx_data"

with open(INPUT_FILENAME, "r") as f:
    lines = f.readlines()

with open(OUTPUT_FILENAME, "w") as f:
    f.write("// Generated with board_data.py. Don't edit manually!\n\n")
    f.write(f"{VAR_TYPE} {VAR_NAME}[] = {{\n")

    for line in lines:
        values = [int(s) for s in line.split(",") if not s.isspace()]
        values = [f"{i:#0{4}x}" if i > 0 else "0xff" for i in values]

        f.write("\t")
        for v in values:
            f.write(f"{v}, ")
        f.write("\n")

    f.write("};")