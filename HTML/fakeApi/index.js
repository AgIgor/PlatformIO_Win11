console.clear();
console.time('teste');

const grid = document.getElementById('grid');

// const listGrid = [];
// const jsonAPI = 'https://jsonplaceholder.typicode.com/photos/'

// for(let i = 1; i <= 100; i++){
//   const req = fetch(`${jsonAPI}${i}`)
//     .then(response => response.json())
//     .then(response=>response)
//     listGrid.push(req);
// }

// async function getAPI(){
//       await Promise.all(listGrid)
//       .then (e=>{
//         // console.log(e)
//         e.forEach((iten)=>{
          
//           const photo = `<img src="${iten.thumbnailUrl}" alt="">`
//           const photos = `<tr>
//                           <td><a href="${iten.url}">${iten.url}</a></td>
//                           <td>${photo}</td>
//                         </tr>`

//           grid.innerHTML += photos

//         })

//       } )
//       .catch( err=> console.log(err) )
//       .finally( ()=>console.log('Finally') )
//       console.log('fim')
// }
// getAPI();




const pokemons = [];
const neededPokemons = [ 1, 2, 3, 4, 5 ];
const pokemonAPI = 'https://pokeapi.co/api/v2/pokemon/'

for (let i = 1; i < 100; i++) {

  url = `${pokemonAPI}${ i }/`
  pokemons.push(fetch(url).then(res => res.json()));

}
getApi()

async function getApi(){
  await Promise.all(pokemons)
  .then (e=>{
    e.forEach((iten)=>{
      console.log(iten.name)
    })
  } )
  .catch( err=> console.log(err) )
  .finally( ()=>console.log('Finally') )
  console.log('fim')
}

const listImg = [];
const imgAPI = 'https://picsum.photos/200/300'

for(let i = 1; i <= 20; i++){
  const req = fetch(`${imgAPI}`)
    .then(response => response.url)
    listImg.push(req);
}

async function getImg(){
  await Promise.all(listImg)
  .then (e=>{
    e.forEach((url, id)=>{
      const photo = `<img src="${url}" alt="">`
      const photos = `<tr>
                      <td><h1>${id}</h1><a href="${url}">${url}</a></td>
                      <td>${photo}</td>
                    </tr>`

      grid.innerHTML += photos

    })
  })

  console.timeEnd('teste')
}

getImg();