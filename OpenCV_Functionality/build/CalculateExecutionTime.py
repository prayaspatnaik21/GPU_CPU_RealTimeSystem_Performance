import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv(r'Execution.csv')

values = []
final_values = []
col_names = [list(df.columns)[0]]

for i in df.values:
    if 'Image Resolution' in i[0]:
        final_values.append(values)
        col_names.append(i[0])
        values = []
        continue
    values.append(i[0])

final_values.append(values)

df_final = pd.DataFrame()

df_final[col_names[0]] = final_values[0]

for i in range(len(col_names)):
    df_final[col_names[i]] = final_values[i]

def Plot(dfImage,columnName):
    plt.xlabel('Iterations')
    plt.ylabel('Execution Time for Rotation')
    dfImage.plot()
    plt.title("Plot for" + " " + columnName)
    plt.show()

for columnName in df_final.columns:
    df_final[columnName] = df_final[columnName].astype('int')
    Plot(df_final[columnName],columnName)
