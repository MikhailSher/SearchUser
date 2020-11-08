const express = require("express");
const bodyParser = require("body-parser");
const app = express();
  
// создаем парсер для данных application/x-www-form-urlencoded
const urlencodedParser = bodyParser.urlencoded({extended: false});
 
app.get("/search", urlencodedParser, function (request, response) {
    response.sendFile(__dirname + "/search.html" );
});
app.post("/search", urlencodedParser, function (request, response) {
    if(!request.body) return response.sendStatus(400);
    //console.log(request.body.userName);

//подключаем аддон
var addon = require('bindings')('addon');

//передаем в аддон имя, которое ввел пользователь и получаем в ответе получаем тот или иной объект
//в зависимости от того,есть такое имя или нет.
var obj1 = addon(`${request.body.userName}`);
if(obj1=="YES"){
response.send(`Пользователь есть`);
}
else {response.send(`Такого пользователя нет`)};

});
  
app.get("/", function(request, response){
    response.send("Главная страница");
});
  
app.listen(3001);