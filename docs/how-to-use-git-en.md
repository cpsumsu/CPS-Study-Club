# How to use Github
Github is powerful of its collaboration tools that allows everyone to make contributions to any public repository (project). But how can we contribute (make changes) to a repository?

## How to Contribute?
Before making any changes, we need to clone (download) the repository from remote to your local machine.
1. Have access to the repository
> If you have access to a repository, which means you can do a push, merge or other actions. You can just clone the repository to your local machine, make changes and push it to the remote repository.

2. Have no access to the repository
> Here's where fork come to place, if you have no access to a repository, you can only fork it to your own repository, clone it, make changes, and finally you make a merge your own repository (changes) into the original repository via pull request.

## Clone the repository
In our case, we grant all of you the write access to the `CPS-Study-Club` if you're a member of us. So you can directly clone the repository and do the push and other actions.
1. Copy the remote URL
Make sure you're in the [root directory](https://github.com/cpsumsu/CPS-Study-Club) of the repository to see the green code button.

<p>
<img width="378" alt="Screenshot 2022-07-31 at 10 10 58 PM" src="https://user-images.githubusercontent.com/82365010/182045483-0d4c0a9b-2613-4c69-aa42-f73ff0fda116.png">


<img width="506" align="right" alt="clone on terminal" src="https://user-images.githubusercontent.com/82365010/182045398-302f88dd-68cb-4cba-8b62-b0a2b514e939.png">
</p>
  

2. Place it to the terminal
```console
# /usr/development/
# Clone the repository directly to under the directory terminal
git clone git@github.com:cpsumsu/CPS-Study-Club.git

# /usr/development/Study-Club/
# If you want to clone only the content of the repository without the root directory
git clone git@github.com:cpsumsu/CPS-Study-Club.git .
```

## Make Contribution
Simply means making changes on your local machine, then upload it to the remote repository. To do so, we need git to recognize the changes of the file.

### How git recognize our changes?
Git will automatically detect any changes of all the files under the repository, but it won't save it without you explicitly tell git to store the changes.
And it can show you where's changed.
1. Show what's changed
```console
git status
```
> For example, when I create a new file, it shows the `untracked files:` and the name of the files.
<img width="615" alt="git status" src="https://user-images.githubusercontent.com/82365010/182045892-c9f952b3-3567-4dd6-a55a-62c1215d2276.png">

> Another case would be making changes to a existing file.
<img width="627" alt="Screenshot 2022-07-31 at 10 26 36 PM" src="https://user-images.githubusercontent.com/82365010/182046009-51a69bf2-e34c-429a-93e3-8e89dfcd521a.png">





