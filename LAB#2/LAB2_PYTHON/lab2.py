import pandas as pd

def initial():
    global categories, expenses
    categories = ['Food', 'Transport', 'Entertainment']
    expenses = {category: pd.DataFrame(columns = ['Item', 'Cost']) for category in categories}

def saveExpense(category, item, cost):
    global expenses
    if category in categories:
        expenses[category] = expenses[category]._append({'Item': item, 'Cost': cost}, ignore_index=True)
        print("Expense saved: %s - %s under %s" %(item, cost, category))
    else:
        print("Invalid category %s. Please choose from %s" %(category, categories))

def finance():
    income = float(input("Please enter you income: "))
    total_expenses = 0.0

    def calculateTotalExpenses():
        nonlocal total_expenses
        for category in categories:
            total_expenses += expenses[category]['Cost'].sum()

    calculateTotalExpenses()
    print("Income: %s, Total Expenses: %s, Remaining Income: %s" %(income, total_expenses, income-total_expenses))

# test
def main():
    initial()
    saveExpense('Food', 'Hamburger', 3)
    saveExpense('Food', 'Strawberry', 5)
    saveExpense('Transport', 'Bus', 0.4)
    saveExpense('Transport', 'Uber', 3)
    saveExpense('Accomodation', 'Rent', 100)
    saveExpense('Entertainment', 'Birthday', 50)
    saveExpense('Entertainment', 'Travelling to Poland', 350)
    saveExpense('Entertainment', 'Christmas Day', 25)
    finance()

if __name__ == "__main__":
    main()