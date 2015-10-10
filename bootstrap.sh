#!/usr/bin/env bash

apt-get update
apt-get upgrade
apt-get install g++
apt-get --assume-yes install gcc-doc gdb-doc srecord
apt-get --assume-yes install subversion git vim llvm gcc
apt-get --assume-yes install build-essential cmake python-dev python-pip zsh curl wget

#Setup VIM
su -l vagrant -c "mkdir ~/.vim/; 
git clone https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim;
cp /vagrant/vimrc ~/.vimrc;
vim +PluginInstall +qall;"

Setup YCM
su -l vagrant -c "cd /home/vagrant/.vim/bundle/YouCompleteMe;
YCM_CORES=2 ./install.py --clang-completer;"

echo "colorscheme solarized
set background=dark
set encoding=utf-8
set t_Co=256
set fillchars+=stl:\\ ,stlnc:\\
set term=xterm-256color
set termencoding=utf-8
set laststatus=2" >> /home/vagrant/.vimrc

echo "
cd /vagrant" >> /home/vagrant/.bashrc

su -l vagrant -c "$(curl -fsSL https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"
chsh -s $(which zsh) vagrant

echo "
cd /vagrant" >> /home/vagrant/.zshrc
su -l vagrant -c "cp /vagrant/agnoster-mod.zsh-theme /home/vagrant/.oh-my-zsh/themes/agnoster-mod.zsh-theme"
su -l vagrant -c "sed -i 's/robbyrussell/agnoster-mod/g' /home/vagrant/.zshrc"
