import subprocess
import os

output = subprocess.check_output("pgrep -af python | grep i3-status-py", shell=True)
output_split = str(output).split(" ")
output = output_split[0]
output = str(output).replace("b'","")
os.system(f"kill -9 {output}")
