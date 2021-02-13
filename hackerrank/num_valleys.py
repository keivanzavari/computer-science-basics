path = "UDDDUDUU"

# U represents an uphill while D is a downhill.
# Start and end at sea level.
#
# A mountain is a sequence of consecutive steps above sea level, starting with a step up from sea level and
# ending with a step down to sea level.
#
# A valley is a sequence of consecutive steps below sea level, starting with a step down from sea level and
# ending with a step up to sea level.
level = 0
entered_valley = False
num_valleys = 0
for step in path:
    if step == "U":
        level += 1
        if level >= 0 and entered_valley:
            num_valleys += 1
            entered_valley = False
    elif step == "D":
        level -= 1
        if level < 0 and not entered_valley:
            entered_valley = True

print(num_valleys)
