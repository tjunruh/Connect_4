```
________/\\\\\\\\\___________________________________________________________________________________________________________/\\\____        
 _____/\\\////////__________________________________________________________________________________________________________/\\\\\____       
  ___/\\\/______________________________________________________________________________________/\\\_______________________/\\\/\\\____      
   __/\\\_________________/\\\\\_____/\\/\\\\\\____/\\/\\\\\\_______/\\\\\\\\______/\\\\\\\\__/\\\\\\\\\\\________________/\\\/\/\\\____     
    _\/\\\_______________/\\\///\\\__\/\\\////\\\__\/\\\////\\\____/\\\/////\\\___/\\\//////__\////\\\////_______________/\\\/__\/\\\____    
     _\//\\\_____________/\\\__\//\\\_\/\\\__\//\\\_\/\\\__\//\\\__/\\\\\\\\\\\___/\\\____________\/\\\_________________/\\\\\\\\\\\\\\\\_   
      __\///\\\__________\//\\\__/\\\__\/\\\___\/\\\_\/\\\___\/\\\_\//\\///////___\//\\\___________\/\\\_/\\____________\///////////\\\//__  
       ____\////\\\\\\\\\__\///\\\\\/___\/\\\___\/\\\_\/\\\___\/\\\__\//\\\\\\\\\\__\///\\\\\\\\____\//\\\\\_______________________\/\\\____ 
        _______\/////////_____\/////_____\///____\///__\///____\///____\//////////_____\////////______\/////________________________\///_____
```

<a href="https://github.com/tjunruh/Connect_4/actions/workflows/pipeline.yml"><img src="https://img.shields.io/github/actions/workflow/status/tjunruh/Connect_4/pipeline.yml?label=build&branch=main"></a>

Console application of Connect 4. It features two player mode and one player mode with easy, moderate, and hard computer levels.

# Windows

The game can be installed by double clicking on the setup executable in the Installation folder.

# Linux

You will need to install the ncurses library if you do not already have it. Run the command below to install it.

```shell
sudo apt-get install libncurses5-dev libncursesw5-dev
```

Simply clone this repository and run the following command:

```shell
make
```

Then enter

```shell
./connect4
```
