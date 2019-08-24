# golfsim
A repository for my project simulating golf matches between some of the greatest golfers of all time.

The main file in this repository is golfsim.cpp, which enables users to run several different types of competitions between golfers. These types of competition rely on www.thealltimegreatestgolfers.com to give indications of the skill level of each historical golfer, which are held in the repository's text files.

The first option for simulation, stroke play, simulates what would happen if the greatest male golfers ever played their careers at the same time. The program gives an indication of how many major tournaments each golfer would win in the amount of years that the user specifies. The second option, match play, simulates a user-specified number of match play tournaments between the greatest golfers ever. The third option, one on one, allows the user to choose any two golfers in the text file they provide and have them face off in as many match play matches as they want. The final option, International, simulates what would happen if the twelve greatest American golfers ever faced off against the twelve greatest European or international golfers ever in a Ryder Cup/President's Cup format.

The command to run the program in your terminal is "./golfsim [filename]". The program will prompt you on how to proceed from there.

There are plenty of opportunities for improvement with this code, some of which are quick fixes and others of which may be long-term goals. My ultimate goal is to employ HTML, CSS, and JavaScript, which I am very unfamiliar with right now, to have this running as a website through GitHub Pages. Another very important goal of mine is to use web scraping to ensure that the program will always have the most up-to-date ratings from thealltimegreatestgolfers.com or wherever the rankings are being fetched from. I also have many other ideas for additional modes and features that I hope to implement soon. These include:

-Selecting a historical player and simulating their career if they played today. Would need a new text file for this.
-Show the leaderboard for a major, with players' scores and any particularly interesting occurrences during the major. This would require switching to a true stroke play method of simulation, something that I'm currently working on.
-Generate FedEx Cup and OWGR points based on how a player finishes in each tournament, show who wins the FedEx Cup or gets the most OWGR points yearly. New FedEx Cup mode would be part of it.

Feel free to tweak any aspect of this you'd like to see changed and create a pull request. I hope you find this at least somewhat interesting, even though I know it's not a definitive indication of what would happen in these scenarios in the slightest. Regardless, it's been a blast for me to make and I look forward to seeing what it can become and what it can help me learn!
