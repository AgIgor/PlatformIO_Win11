
switchTheme.checked = localStorage.getItem("theme");

if(localStorage.getItem("theme")) document.documentElement.style.setProperty("color-scheme", 'dark');
else document.documentElement.style.setProperty("color-scheme", 'light');

function toggleTheme(t){
    
  if(t.checked){
    document.documentElement.style.setProperty("color-scheme", 'dark');
    localStorage.setItem("theme", true);
  }
  else{
    document.documentElement.style.setProperty("color-scheme", 'light');
    localStorage.setItem("theme", false);
  }
}


function toggleBtn(id){
  console.log(id.id, id.checked);
  localStorage.setItem(id.id, id.checked);
}