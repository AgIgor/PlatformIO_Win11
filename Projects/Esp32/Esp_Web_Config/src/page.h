const char index_html[] PROGMEM = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
        <title>Controle de Pinos ESP32</title>
        <style>
            body {
                font-family: Arial, sans-serif;
                margin: 20px;
            }
            table {
                width: 100%;
                border-collapse: collapse;
                margin-bottom: 20px;
            }
            tr:hover{
                background-color: #f5f5f5;
            }
            th, td {
                border: 1px solid  #ddd;;
                padding: 8px;
                text-align: center;
            }
            th {
                background-color: #f2f2f2;
            }
            select {
                width: 100%;
                padding: 5px;
            }
            button{
                padding: 10px 20px;            
                color: white;
                border: none;
                cursor: pointer;
                margin: 5px 0px;
                background-color: #4CAF50;
            }
            .btn-add{
            }
            .btn-del{
                background-color: #af4c4c;
            }
        </style>
    </head>
    <body>
        <h1>Controle de Pinos ESP32</h1>

        <select id="pinSelect">
            <option value="">Selecione um pino</option>
        </select>

        <button id="addPinButton">Adicionar Pino</button>

        <table id="pinTable">
            <thead>
                <tr>
                    <th>Pino</th>
                    <th>Tipo</th>
                    <th>Valor/Estado</th>
                    <th>Remover</th>
                </tr>
            </thead>
            <tbody>
            </tbody>
        </table>

        <script>
            const pins = [
                { name: "GPIO0", functions: ["Digital", "Analog"] },
                { name: "GPIO1", functions: ["Digital", "Analog"] },
                { name: "GPIO2", functions: ["Digital"] },
                // ... Defina todos os pinos e suas funções aqui
                { name: "GPIO36", functions: ["Analog"] },
                { name: "GPIO39", functions: ["Analog"] }
            ];

            const pinSelect = document.getElementById("pinSelect");
            const addPinButton = document.getElementById("addPinButton");
            const pinTable = document.getElementById("pinTable").getElementsByTagName('tbody')[0];
            // const websocket = new WebSocket("ws://SEU_IP_ESP32:81/"); // Substitua pelo IP do seu ESP32

            // websocket.onopen = () => {
            //     console.log("Conectado ao Websocket");
            // };

            // websocket.onmessage = (event) => {
            //     const data = JSON.parse(event.data);
            //     for (const pinData of data.pins) {
            //         const row = document.getElementById(pinData.name);
            //         if (row) {
            //             const valueCell = row.cells[2];
            //             if (valueCell.firstChild && valueCell.firstChild.type == "checkbox") {
            //                 valueCell.firstChild.checked = pinData.value == 1;
            //             } else if (valueCell.firstChild && valueCell.firstChild.type == "number") {
            //                 valueCell.firstChild.value = pinData.value;
            //             }
            //         }
            //     }
            // };

            pins.forEach(pin => {
                const option = document.createElement("option");
                option.value = pin.name;
                option.text = pin.name;
                pinSelect.appendChild(option);
            });

            addPinButton.addEventListener("click", () => {
                const selectedPin = pinSelect.value;
                if (selectedPin && !document.getElementById(selectedPin)) {
                    addPinToTable(selectedPin);
                }
            });

            function addPinToTable(pinName) {
                const row = pinTable.insertRow();
                row.id = pinName;

                const nameCell = row.insertCell();
                const typeCell = row.insertCell();
                const valueCell = row.insertCell();
                const removeCell = row.insertCell();

                nameCell.textContent = pinName;

                const typeSelect = document.createElement("select");
                typeSelect.innerHTML = `<option value=''>Selecione</option>
                                        <option value='digital_out'>Saída Digital</option>
                                        <option value='digital_in'>Entrada Digital</option>
                                        <option value='analog_out'>Saída Analógica</option>
                                        <option value='analog_in'>Entrada Analógica</option>`;
                typeCell.appendChild(typeSelect);

                let currentValueElement; // Variável para armazenar o elemento de valor atual

                function updateValueCell(sendConfig = true) {
                    valueCell.innerHTML = "";
                    const selectedType = typeSelect.value;

                    if (selectedType === "digital_out") {
                        const checkbox = document.createElement("input");
                        checkbox.type = "checkbox";
                        checkbox.addEventListener("change", () => {
                            // websocket.send(JSON.stringify({ pin: pinName, value: checkbox.checked ? 1 : 0, mode: "digitalWrite", type: selectedType }));
                            console.log(JSON.stringify({ pin: pinName, value: checkbox.checked ? 1 : 0, mode: "digitalWrite", type: selectedType }));
                            
                        });
                        valueCell.appendChild(checkbox);
                        currentValueElement = checkbox;
                    } else if (selectedType === "analog_out") {
                        const numberInput = document.createElement("input");
                        numberInput.type = "number";
                        numberInput.addEventListener("change", () => {
                            // websocket.send(JSON.stringify({ pin: pinName, value: parseInt(numberInput.value), mode: "analogWrite", type: selectedType }));
                            console.log(JSON.stringify({ pin: pinName, value: parseInt(numberInput.value), mode: "analogWrite", type: selectedType }));
                            
                        });
                        valueCell.appendChild(numberInput);
                        currentValueElement = numberInput;
                    } else if (selectedType.endsWith("_in")) {
                        if (selectedType.startsWith("digital")){
                            const checkbox = document.createElement("input");
                            checkbox.type = "checkbox";
                            checkbox.disabled = true;
                            valueCell.appendChild(checkbox);
                            currentValueElement = checkbox;
                        } else if (selectedType.startsWith("analog")){
                            const numberInput = document.createElement("input");
                            numberInput.type = "number";
                            numberInput.disabled = true;
                            valueCell.appendChild(numberInput);
                            currentValueElement = numberInput;
                        }
                    }
                    if (sendConfig) {
                        // websocket.send(JSON.stringify({ pin: pinName, type: selectedType, mode: "config" }));
                        console.log(JSON.stringify({ pin: pinName, type: selectedType, mode: "config" }));
                        
                    }
                }

                typeSelect.addEventListener("change", () => updateValueCell());
                updateValueCell(false); // Envia a configuração inicial

                const removeButton = document.createElement("button");
                removeButton.textContent = "Remover";
                removeButton.classList.add("btn-del");
                removeButton.addEventListener("click", () => {
                    row.remove();
                });
                removeCell.appendChild(removeButton);
            }        
        </script>
    </body>
    </html>
)rawliteral";