import requests
import tkinter as tk

def search_word():
    word = entry.get()
    if not word:
        result_label.config(text="❌ Please enter a word.")
        return

    url = f"https://api.dictionaryapi.dev/api/v2/entries/en/{word}"
    response = requests.get(url)

    if response.status_code != 200:
        result_label.config(text="❌ Word not found.")
        return

    data = response.json()[0]

    # 단어 기본 정보
    meanings = data["meanings"][0]
    definition = meanings["definitions"][0]["definition"]
    part_of_speech = meanings["partOfSpeech"]
    phonetic = data.get("phonetic", "")

    result_text = f"""
📘 Word: {word.title()}
🔊 Phonetic: {phonetic}
📚 Part of Speech: {part_of_speech}
📝 Definition:
{definition}
"""
    result_label.config(text=result_text)

# --- tkinter UI 구성 ---
root = tk.Tk()
root.title("Mini English Dictionary 📖")
root.geometry("400x350")
root.resizable(False, False)

title = tk.Label(root, text="Enter an English word", font=("Arial", 14))
title.pack(pady=10)

entry = tk.Entry(root, font=("Arial", 12), width=30)
entry.pack(pady=5)

button = tk.Button(root, text="Search", font=("Arial", 12), command=search_word)
button.pack(pady=10)

result_label = tk.Label(root, text="", font=("Arial", 11), justify="left", wraplength=350)
result_label.pack(pady=10)

root.mainloop()
