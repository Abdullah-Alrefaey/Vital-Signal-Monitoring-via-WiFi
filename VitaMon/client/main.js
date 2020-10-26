import { Template } from 'meteor/templating';
import 'bootstrap/dist/css/bootstrap.min.css'
import './main.html';
// Load Library
const firebase = require('firebase-admin');

// get service key file
const servicekey = require('../esp-1st-project-firebase-adminsdk-atckp-7d0a35b5d7.json');

// Init App

function rand(){
  return Math.random();
}
Template.body.events({
  'click button'(event, instance) {
    firebase.initializeApp({
      credential: firebase.credential.cert(servicekey),
      databaseURL: 'https://esp-1st-project.firebaseio.com'
    });
  
  
  let datapoint = firebase.database().ref();
  let data = datapoint.child("Reading");
  data.on("value", (snap)=>{
      let time = new Date();

      let update = {
        x:  [[time]],
        y: [[snap.val()]]
      }

      let olderTime = time.setMinutes(time.getMinutes() - 1);
      let futureTime = time.setMinutes(time.getMinutes() + 1);

      let minuteView = {
        xaxis: {
          type: 'date',
          range: [olderTime,futureTime]
        }
      };

      Plotly.relayout('graph', minuteView);
      Plotly.extendTraces('graph', update, [0])
  });
  },
});