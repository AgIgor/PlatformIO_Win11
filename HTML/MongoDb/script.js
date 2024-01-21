const url = 'https://sa-east-1.aws.data.mongodb-api.com/app/data-odkfx/endpoint/data/v1/action/find?secret=1234igor'

console.log(url)

//setInterval(()=>{

  const headers = {
    'Content-Type': 'application/json',
    'api-key': 'ed4QaaObPZKC7UWnqu5tZxFm0fv1RJ7RghRtPy20hRZf9aCsOtjSJuthjG7wOSRL',
    'Host': 'sa-east-1.aws.data.mongodb-api.com',
    'Connection': 'keep-alive',
    // 'Authorization': 'Bearer '
};

  const body = {
    "dataSource":"Cluster0",
    "database": "esp32",
    "collection": "CHIP_ID_0001",
    "sort":{ "_id" : -1}
}

  const fetchPromise = fetch(url, {
    mode: "no-cors",
    method: 'POST',
    headers: headers,
    body: body
  });

  fetchPromise.then((response) => {
    console.log(response.status);
  });





//},5000)
