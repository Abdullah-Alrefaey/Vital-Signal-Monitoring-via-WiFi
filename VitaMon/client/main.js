import { Template } from 'meteor/templating';
import 'bootstrap/dist/css/bootstrap.min.css'
import './main.html';

// Load Library
const firebase = require("firebase/app");

// Add the Firebase products that you want to use
require("firebase/auth");
require("firebase/firestore");
require("firebase/database");

let firebaseConfig = {
    apiKey: "AIzaSyA4BPzcuUubdN_1nF1BXE7xfHfv9Ie5en8",
    authDomain: "esp-1st-project.firebaseapp.com",
    databaseURL: "https://esp-1st-project.firebaseio.com",
    projectId: "esp-1st-project",
    storageBucket: "esp-1st-project.appspot.com",
    messagingSenderId: "510468231747",
    appId: "1:510468231747:web:5aca299e55925b3d1ffaf6",
    measurementId: "G-TZZH9RVXMH"
};

Template.body.events({
  'click button'(event, instance) {
      firebase.initializeApp(firebaseConfig);

  // Connect to database
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