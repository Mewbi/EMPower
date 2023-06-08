#!/usr/bin/env python3

import json
import time
import asyncio
import websockets
import random as rd

data = {}

# I will remove this function
def fakeData():
    dataTimestamp = time.time()
    value = rd.random() * 10
    data["date"] = dataTimestamp
    data["value"] = value
    return data

async def generateData():
    print("Generating data")
    
    while True:
        dataTimestamp = time.time()
        value = rd.random() * 10
        data["date"] = dataTimestamp
        data["value"] = value


async def handler(websocket):
    print("Accept connection")
    message = await websocket.recv()
    print("Receive: {}".format(message))
    event = json.loads(message)

    if event["ready"] != True:
        return
    
    while True:
        d = fakeData()
        await websocket.send(json.dumps(d))
        print("Sended: {}".format(d))

        time.sleep(0.1) # Sleep 100 ms


async def startWebsocket():
    print("Start Websocket")
    async with websockets.serve(handler, "", 8001):
        await asyncio.Future()  # Run forever

async def main():
    websocketServerTask = asyncio.create_task(startWebsocket())
    #generateDataTask = asyncio.create_task(generateData())

    await websocketServerTask
    #await generateDataTask

if __name__ == "__main__":
    asyncio.run(main())