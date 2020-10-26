import { Template } from 'meteor/templating';
import 'bootstrap/dist/css/bootstrap.min.css'
import './main.html';

function rand(){
  return Math.random();
}
Template.body.events({
  'click button'(event, instance) {
    let interval = setInterval(function() {

      let time = new Date();

      let update = {
        x:  [[time]],
        y: [[rand()]]
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

    }, 50);
  },
});