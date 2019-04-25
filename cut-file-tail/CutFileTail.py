import sys

if len(sys.argv) != 4:
    print("请传入三个参数！")
    exit()

FirstSegment = True

with open(sys.argv[1],"r",encoding="utf-8") as r:
    with open(sys.argv[2],"w",encoding="utf-8") as w:
            for line in r:
                if not line.startswith(sys.argv[3]):
                    w.write(line)
                elif FirstSegment:
                    FirstSegment = False
                else:
                    exit()


