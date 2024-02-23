// const fs = require('fs');

const sampleObjectPhone = {
    phone: '11 123456789'
};
const sampleObject = {
    name: 'igor',
    member: 'ag',
    type: {
        x: 77,
        y: 33
    }
};

/* fs.writeFile("./object.json", JSON.stringify(sampleObject, null, 4), (err) => {
    if (err) {
        console.error(err);
        return;
    };
    console.log("File has been created");
}); */

/* fs.readFile('./object.json', 'utf8', function readFileCallback(err, data){
    if (err){
        console.log(err)
    } else {
    obj = JSON.parse(data)
    obj.
    json = JSON.stringify(obj)
    console.log(obj.type.phone)
    //fs.writeFile('myjsonfile.json', json, 'utf8', callback)
}}); */

const posts = require("./object.json")
// const post = posts.find(post => post.id === Number(id))     
//console.log(posts.find(post => post.name === "igor2"))
console.log(posts)
