function referencias() {
    const imgset = document.getElementsByTagName("img");
    let output = "";
    for (let i = 0; i < imgset.length; i++) {
      output += `<p> Source for image ${i + 1}: ${imgset[i].src}</p>`;
    }
    document.getElementById("info").innerHTML = output;
  }


  function GestionarMouse(idImg, idCaption, nuevaSrc, calificacion, mostrar) {
    const imgElement = document.getElementById(idImg);
    const captionElement = document.getElementById(idCaption);
    imgElement.src = nuevaSrc;
    captionElement.innerText = mostrar ? calificacion : "";
    if (mostrar) {
      imgElement.style.height = "400px";
      imgElement.style.width = "600px";
      
    } else {
      imgElement.style.height = "500px"; // Tamaño original de las imágenes
      imgElement.style.width = "300px";
    }
  }
  