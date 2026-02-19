# Contributing to Arcweave Unreal plugin

*This is a work-in-progress document.*

## I Have a Question

> If you want to ask a question, we assume that you have read the available [Documentation](https://github.com/arcweave/arcweave-unreal-plugin/) and seen the [Tutorial](https://www.youtube.com/playlist?list=PLP2s5PcDiBdYRg0zHpJTuiDVf9JF_inyH) videos.

Before you ask a question, it is best to search for
existing issues [on github](https://github.com/arcweave/arcweave-unreal-plugin/issues) 
or on [the Discord server](https://discord.gg/kb4FxBxw)
that might help you.

In case you have found a suitable issue and still need clarification, you can write your question in this issue.
It is also advisable to search the internet for answers first.

If you then still feel the need to ask a question and need clarification, we recommend the following:

- Open an issue [on github](https://github.com/arcweave/arcweave-unreal-plugin/issues/new) and post in the "aw-help" channel on the Discord server.
- Provide as much context as you can about what you're running into.
- Provide a short example that shows the issue.
- Specify which version you are using and whether you are using Arcweave through a plugin.

We will then take care of the issue as soon as possible.


## I Want To Contribute


### Reporting Bugs

#### Before Submitting a Bug Report

A good bug report shouldn't leave others needing to chase you up for more information. Therefore, we ask you to investigate carefully, collect information and describe the issue in detail in your report. Please complete the following steps in advance to help us fix any potential bug as fast as possible.

- Make sure that you are using the latest version.
- Also make sure to search the Discord channel mentioned above or the internet to see if users outside of the GitHub community have discussed the issue.


#### How Do I Submit a Good Bug Report?

We use GitHub issues to track bugs and errors. If you run into an issue with the project:

Before you submit a report, it is best to search for
existing issues [on github](https://github.com/arcweave/arcweave-unreal-plugin/issues) 
or on [the Discord server](https://discord.gg/kb4FxBxw)


- Open an issue [on github](https://github.com/arcweave/arcweave-unreal-plugin/issues) 
and also on [the Discord server](https://discord.gg/kb4FxBxw).
- Explain the behavior you would expect and the actual behavior.
- Please provide as much context as possible and describe the *reproduction steps* that someone else can follow to recreate the issue on their own. This can include your code.
- For good bug reports you should isolate the problem and create a reduced test case.

### Suggesting Enhancements

This section guides you through submitting an enhancement suggestion for the
Arcweave Unreal plugin, **including completely new features and minor improvements to existing functionality**. Following
these guidelines will help maintainers and the community to understand your suggestion and find related suggestions.

#### Before Submitting an Enhancement

- Make sure that you are using the latest version.
- Read the [documentation](ttps://github.com/arcweave/arcweave-unreal-plugin/) carefully and find out if the functionality is already covered, perhaps via configuration options.
- Search [GitHub issues](https://github.com/arcweave/arcweave-unreal-plugin/issues) or [the Discord server](https://discord.gg/kb4FxBxw); you can check both the channel "aw-whishlist" and "unreal-plugin" to see if the enhancement has already been suggested. If it has, add a comment to the existing issue instead of opening a new one.
- Find out whether your idea fits with the scope and aims of the project. It's up to you to make a strong case to convince the project's developers of the merits of this feature. Keep in mind that we want features that will be useful to the majority of our users and not just a small subset. *If you're just targeting a minority of users, consider writing an add-on/plugin library*.

### How Do I Submit a Good Enhancement Suggestion?

- Use a **clear and descriptive title** for the issue to identify the suggestion.
- Provide a **step-by-step description of the suggested enhancement** in as many details as possible.
- **Describe the current behavior** and **explain which behavior you expected to see instead** and why. At this point you can also tell which alternatives do not work for you.
- You may want to **include some existing diagram examples** that would help to understand the suggestion.
- **Explain why this enhancement would be useful** to most Arcweave plugin users. You may also want to point out other projects that solve it better and which could serve as inspiration.

### Your First Code Contribution

#### Good First Issues
  Start with issues labeled:
  - [good first issue](hhttps://github.com/arcweave/arcweave-unreal-plugin/issues?q=label%3A%22good%20first%20issue%22)
  - [documentation](https://github.com/arcweave/arcweave-unreal-plugin/issues?q=label%3Adocumentation)

#### Environment Setup
1. **Prerequisites:**
  - [IDE: VS Code, Visual Studio or Rider](https://visualstudio.microsoft.com/it/vs/older-downloads/) - version 2022 or newer
  - [Unreal Engine 5.](https://www.unrealengine.com/en-US/download) - version 5.5.4
  - [Git](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git) - to clone the repository and manage the version control

If you chose Visual Studio and you have trouble getting Unreal to start, follow this [guide](https://dev.epicgames.com/documentation/en-us/unreal-engine/setting-up-visual-studio-development-environment-for-cplusplus-projects-in-unreal-engine?application_version=5.5)

2. **Fork the Arcweave repository** 
Now you have two options:
- Fork just the plugin repository by [clicking here](https://github.com/arcweave/arcweave-unreal-plugin/fork)
- Fork the plugin repository and connect it to the demo Unreal project in order to create an environment where you can test your changes easily. This guide will follow the second approach

3. **Clone the Unreal demo project**
- After you forked the plugin repo, clone the project in an empty folder using this command

```sh
git clone https://github.com/arcweave/arcweave-unreal-example.git
```

4. **Navigate to the arcweave plugin folder**
Once the project is cloned, navigate to the folder "ArcweaveDemo/Plugins/" (e.g D:\Progetti\arcweave-unreal-example-main\ArcweaveDemo\Plugins).
Then open a Bash console and run:

```sh
git init
```
then go to the fork of the arcweave plugin and copy the URL that you find by clicking "Code" and then under "HTTPS" (for example: https://github.com/salvolannister/arcweave-unreal-plugin.git). Then run:

```sh
git remote add YOUR_URL
```

#### Making Changes

**1. Create feature branch:**

```sh
git checkout -b add/issue-description
```
**2. Commit and push changes**:
```sh
git commit -am "✨ add new feature" (It is necessary to follow the commit messages styleguide)
git push
```
**3. Update local fork with latest changes**
If you incur conflicts or your local fork is not up-to-date, you can run:

Go to your pull request branch, open a Bash console and add the original repository as an `upstream` remote:

```sh
git remote add upstream https://github.com/arcweave/arcweave-unreal-example.git
```

You now have two remotes: one for your fork, and one for the original repository. If you run `git remote -v`, you will see something like:

```sh
git remote -v
origin  https://github.com/myusername/myfork.git (fetch)
origin  https://github.com/myusername/myfork.git (push)
upstream        https://github.com/arcweave/arcweave-unreal-example.git (fetch)
upstream        https://github.com/arcweave/arcweave-unreal-example.git(push)
```

Then, track and update the remote branches by fetching them from `upstream`:

```sh
git fetch upstream
```

Next, go back to your fork's default branch (usually `master` or `main`) and rebase it on top of the upstream default branch:

```sh
git checkout main
git rebase upstream/main
```

To fully sync your fork on GitHub, push the rebased branch to your remote:

```sh
git push origin +main
```

Now rebase your current feature branch on top of your fork's latest `origin`:

```sh
git rebase origin
```

#### Submitting PR

  **Open PR against plantuml:master**
  > PR should contain: 
  > 1) A title that briefly describes the essence of the changes; 
  > 2) A description that can explain in detail the essence of the changes: 
  You can follow this template:
  - what the pull request is about
  - why the changes were needed
  - possible shortcomings

## Styleguides
### Commit Messages - [Full Guide](https://github.com/plantuml/plantuml/blob/master/docs/CONVENTIONAL_COMMIT.md)

#### Format
```plaintext
[optional scope]: <description>

[optional body]
[optional footer(s)]
```

- Use the **imperative, present tense** (e.g., "fix", "add", "remove").
- Avoid capitalizing the first letter.
- Do not end with a period (.).

### Unreal cpp
Try to follow the conventions already used in the code
---
