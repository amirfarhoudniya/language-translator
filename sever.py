from flask import Flask, request, jsonify

app = Flask(__name__)

# Dummy translation function
def translate_text(target_lang , text):
    # For demonstration purposes, this function just reverses the text
    # In a real application, you would integrate with a translation API
    return text[::-1]

@app.route('/translate', methods=['POST'])
def translate():
    data = request.get_json()
    if not data or 'text' not in data or 'target_lang' not in data:
        return jsonify({'error': 'Invalid input'}), 400


    target_lang = data['target_lang']
    source_text = data['text']

    # Perform the translation (dummy implementation here)
    translated_text = translate_text(target_lang , source_text)

    return jsonify({'translated_text': translated_text})

if __name__ == '__main__':
    app.run(debug=True, host='127.0.0.1', port=5000)
