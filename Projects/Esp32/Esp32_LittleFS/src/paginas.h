static const char configPage[] PROGMEM =
    R"(
    <!DOCTYPE html>
    <html lang="pt-BR">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Conexão Wi-Fi</title>
        
        <style>
            * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }

        body {
            font-family: Arial, sans-serif;
            background-color: #f0f0f0;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
        }

        .container {
            background-color: #fff;
            padding: 20px 30px;
            border-radius: 10px;
            box-shadow: 0 2px 10px rgba(0, 0, 0, 0.1);
            text-align: center;
        }

        h1 {
            margin-bottom: 20px;
            font-size: 24px;
            color: #333;
        }

        form {
            display: flex;
            flex-direction: column;
            align-items: center;
        }

        label {
            margin-bottom: 10px;
            font-size: 18px;
            color: #555;
        }

        select, input[type="password"] {
            width: 100%;
            padding: 10px;
            margin-bottom: 20px;
            border: 1px solid #ccc;
            border-radius: 5px;
            font-size: 16px;
        }

        button {
            padding: 10px 20px;
            font-size: 16px;
            color: #fff;
            background-color: #007bff;
            border: none;
            border-radius: 5px;
            cursor: pointer;
            transition: background-color 0.3s ease;
        }

        button:hover {
            background-color: #0056b3;
        }

        </style>
    </head>
    <body>
        <div class="container">
            <h1>Conexão Wi-Fi</h1>
            <form id="wifi-form" method="post" action="/conectar">
                <label for="ssid">Nome da Rede Wi-Fi:</label>
                <select id="ssid" name="ssid">
                    <option value="rede1">Rede Wi-Fi 1</option>
                    <option value="rede2">Rede Wi-Fi 2</option>
                    <option value="rede3">Rede Wi-Fi 3</option>
                    <option value="rede4">Rede Wi-Fi 4</option>
                </select>

                <label for="password">Senha do Wi-Fi:</label>
                <input type="password" id="password" name="password" placeholder="Digite a senha">
                
                <button type="submit">Conectar</button>
            </form>
        </div>
    </body>
    </html>

)";

static const char loginPage[] PROGMEM =
    R"(
    <!DOCTYPE html>
    <html lang="pt-BR">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Conexão Wi-Fi</title>
        <style>
            * {
                margin: 0;
                padding: 0;
                box-sizing: border-box;
            }

            body {
                font-family: Arial, sans-serif;
                background-color: #f0f0f0;
                display: flex;
                justify-content: center;
                align-items: center;
                height: 100vh;
            }

            .container {
                background-color: #fff;
                padding: 20px 30px;
                border-radius: 10px;
                box-shadow: 0 2px 10px rgba(0, 0, 0, 0.1);
                text-align: center;
            }

            h1 {
                margin-bottom: 20px;
                font-size: 24px;
                color: #333;
            }

            form {
                display: flex;
                flex-direction: column;
                align-items: center;
            }

            label {
                margin-bottom: 10px;
                font-size: 18px;
                color: #555;
            }

            input[type="text"] {
                width: 100%;
                padding: 10px;
                margin-bottom: 20px;
                border: 1px solid #ccc;
                border-radius: 5px;
                font-size: 16px;
            }

            button {
                padding: 10px 20px;
                font-size: 16px;
                color: #fff;
                background-color: #007bff;
                border: none;
                border-radius: 5px;
                cursor: pointer;
                transition: background-color 0.3s ease;
            }

            button:hover {
                background-color: #0056b3;
            }

        </style>
    </head>
    <body>

        <div class="container">
            <h1>Conexão Wi-Fi</h1>
            <form id="wifi-form" action="/submit" method="POST">
                <label for="password">Senha do Wi-Fi:</label>
                <input type="text" id="password" name="password" placeholder="Digite a senha">
                <button type="submit">Conectar</button>
            </form>
        </div>

    </body>
    </html>

)";