
const data = require('./build/Release/binding.node');
 

function callEmit(arg)
{
    console.log(arg);
}
 
let a = data.CreateFunction({tsfn: callEmit});
let objWrap = data.CreateObject();
 
