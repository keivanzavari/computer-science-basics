# You have X amount of money in year 1 and the prices of different stocks in year 1 & year 2.
# How much of each stock should you have bought in year 1 to maximize profits when you sell everything in year 2?

total = 20
stocks = {"apple": [12, 39], "pear": [15, 45], "orange": [10, 13], "lemon": [18, 47]}
# maximum number of stocks you can buy from each company depends on X//company
max_stocks = {}
cheapest = 1e5
for k in stocks.keys():
    max_stocks[k] = total // stocks[k][0]
    cheapest = min(cheapest, stocks[k][0])
print(max_stocks)


total_end = total
for k in stocks.keys():
    # each option means that we have bought x stocks from that company
    for num_stocks in max_stocks[k]:
