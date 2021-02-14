strings = ["ab", "abc", "ab", "cd", "ef"]

queries = ["ab", "cd", "fh"]

for query in queries:
    count = strings.count(query)
    print(count)
