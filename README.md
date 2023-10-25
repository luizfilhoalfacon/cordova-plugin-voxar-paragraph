---
title: pARagraph
description: Use pARagraph API
---
<!--
/* Voxar Labs - CIn/UFPE, Recife, Brazil
*
* Copyright(c) 2017-2018 by Voxar Labs - CIn/UFPE
*
* This software is the confidential and proprietary information
* of Voxar Labs - Center of Informatics of the Federal University 
* of Pernambuco ("Confidential Information"). You
* shall not disclose such Confidential Information and shall use
* it only in accordance with the terms of the license agreement
* you entered into with Voxar Labs CIn/UFPE.
*
* Description: pARagraph technology.
*
* @author João Gabriel Santiago Mauricio de Abreu (jgsma@cin.ufpe.br),
*         João Marcelo Xavier Natário Teixeira (jmxnt@cin.ufpe.br),
*         Lucas Oliveira Maggi (lom@cin.ufpe.br),
*         Veronica Teichrieb (vt@cin.ufpe.br).
*
* @since 2017-04-07
*/
-->

# cordova-plugin-voxar-paragraph

This plugin provides access to pARagraph's native API `navigator.voxarparagraph` object.

Although the object is attached to the global scoped `navigator`, it is not available until after the `deviceready` event.

    document.addEventListener("deviceready", onDeviceReady, false);
    function onDeviceReady() {
        console.log(navigator.voxarparagraph);
    }

Report issues to voxarlabs@cin.ufpe.br

## Installation

    cordova plugin add cordova-plugin-voxar-paragraph

## Methods

- `navigator.voxarparagraph.init`
- `navigator.voxarparagraph.open`
- `navigator.voxarparagraph.retrieveFromPath`

## navigator.voxarparagraph.init

Initialize pARagraph system.

    navigator.voxarparagraph.init(paragraphPath, completeCallback)

- __paragraphPath__: Path to temporary files of pARagraph. _(String)_

- __completeCallback__: Callback to invoke when ready. _(Function)_


## navigator.voxarparagraph.open

Open a pARagraph database file.

    navigator.voxarparagraph.open(databasePath, completeCallback)

- __databasePath__: Path to database file. _(String)_

- __completeCallback__: Callback to invoke when ready. _(Function)_


## navigator.voxarparagraph.retrieveFromPath

Retrieve a document id from the loaded database.

    navigator.voxarparagraph.retrieveFromPath(imgPath, completeCallback)

- __imgPath__: Path to the image file to be identified. _(String)_

- __completeCallback__: Callback to invoke when ready. _(Function)_

