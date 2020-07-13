const jayson = require('jayson');

// create a client
const client = jayson.client.http('http://localhost:8077/jsonrpc')
 
// invoke "add"

client.request('add', [1, 1], function(err, response) {
  if(err) throw err;
  console.log('1 + 1 =', response.result); // 2
});

client.request('echo', ["hello world"], (err, response) => {
  if (err) throw err;
})

console.log("Closing in 5...")

for ( let i = 4; i >= 1; i--) {
  setTimeout(() => {
    console.log(`${i}...`)
  }, 1000 * (4 - i + 1))
}

setTimeout(() => {
  console.log("Sending 'finish'")
  client.request('finish', [], (err,response) => {
    if (err) throw err;
    console.log("done")
  })
}, 5000)