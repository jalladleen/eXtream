"use strict";


let userList = document.querySelector("ui.contacts");

let url = window.location.href;
url = url.replace('?', '');

let currentSong = "default_song.mp3";
let songInfo = document.querySelector("#SongInfo");
let audio = document.querySelector("audio");

function GetUsers()
{
    $.ajax({
        type: "GET",
        url: url + "/UserList",
        data: '',
        success: function (result) {
           console.log(result);
           userList.innerHTML = result;
        },
        dataType: "text"
      });
}

function GetSongInfo()
{
    $.ajax({
        type: "GET",
        url: url + "/SongInfo",
        data: '',
        success: function (result) {
           console.log(result);

            if (result["State"] === "Paused")
            {
                audio.pause();
            }

            if (result["State"] === "Playing")
            {
                if (audio.paused) audio.play();

                if (Math.abs(audio.currentTime - result["Time"]) > 5.0)
                {
                    audio.currentTime = result["Time"];
                }
            }

           if (result["SongName"] !== currentSong)
           {
            songInfo.innerHTML = result["SongName"] + " uploaded by " + result["SongUploader"];

            audio.setAttribute("src", "/songs/" + result["SongName"]);
            currentSong = result["SongName"];
           }

        },
        dataType: "json"
      });
}

function SendSongControlPlay()
{
    $.ajax({
        type: "POST",
        url: url + "/SongControl",
        data: { Action: "Play", Time: `${audio.currentTime}` },
        success: function (result) {


        },
        dataType: "text"
      });
}

function SendSongControlPause()
{
    $.ajax({
        type: "POST",
        url: url + "/SongControl",
        data: { Action: "Pause" },
        success: function (result) {

        },
        dataType: "text"
      });
}

function SendSongControlEnd()
{
    $.ajax({
        type: "POST",
        url: url + "/SongControl",
        data: { Action: "Reset" },
        success: function (result) {
            audio.currentTime = 0;
        },
        dataType: "text"
      });
}

audio.addEventListener("play", SendSongControlPlay);
audio.addEventListener("pause", SendSongControlPause);
audio.addEventListener("ended", SendSongControlEnd);

setInterval(GetUsers, 15000);

setInterval(GetSongInfo, 1000);




