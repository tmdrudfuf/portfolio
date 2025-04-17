import requests
import tkinter as tk

API_KEY = "71e663627f924b6aaed230356251704"

def show_animated_popup(title, message):
    popup = tk.Toplevel()
    popup.title(title)
    popup.geometry("300x150+500+800")  # 시작 위치: 아래쪽
    popup.resizable(False, False)
    popup.configure(bg="#fefefe")

    label = tk.Label(popup, text=message, font=("Arial", 11), bg="#fefefe")
    label.pack(pady=20)

    close_btn = tk.Button(popup, text="OK", command=popup.destroy, font=("Arial", 11), bg="#4caf50", fg="white", width=10)
    close_btn.pack(pady=10)

    popup.grab_set()

    # 애니메이션: 아래에서 위로 올라오기
    def animate(y):
        if y > 300:
            popup.geometry(f"300x150+500+{y}")
            popup.after(10, lambda: animate(y - 10))
        else:
            popup.geometry("300x150+500+300")

    animate(800)

def get_weather():
    city = city_entry.get()
    if not city:
        show_animated_popup("Input Error", "Please enter a city name.")
        return

    url = f"http://api.weatherapi.com/v1/current.json?key={API_KEY}&q={city}"
    response = requests.get(url).json()

    if "error" in response:
        result_label.config(text="❌ City not found.\n" + response["error"]["message"])
        return

    weather = response["current"]["condition"]["text"]
    temp = response["current"]["temp_c"]
    feels_like = response["current"]["feelslike_c"]
    humidity = response["current"]["humidity"]

    result = f"""
📍 Weather in {city.title()}:
🌤️ Condition: {weather}
🌡️ Temp: {temp}°C (Feels like {feels_like}°C)
💧 Humidity: {humidity}%
"""
    result_label.config(text=result)

# ---------- UI 구성 ----------
root = tk.Tk()
root.title("Simple Weather App")
root.geometry("360x260")
root.resizable(False, False)

city_label = tk.Label(root, text="Enter city name (e.g. seoul):", font=("Arial", 12))
city_label.pack(pady=10)

city_entry = tk.Entry(root, font=("Arial", 12), width=30)
city_entry.pack()

search_button = tk.Button(root, text="Get Weather", font=("Arial", 12), command=get_weather)
search_button.pack(pady=10)

result_label = tk.Label(root, text="", font=("Arial", 11), justify="left")
result_label.pack(pady=10)

root.mainloop()
