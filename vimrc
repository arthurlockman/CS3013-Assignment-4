syntax on
set mouse=a
set smartindent
set tabstop=4
set shiftwidth=4
set expandtab
set number
set backspace=indent,eol,start
set splitbelow
set splitright
set incsearch           " search as characters are entered
set hlsearch            " highlight matches
highlight clear SignColumn

nnoremap <C-J> <C-W><C-J>
nnoremap <C-K> <C-W><C-K>
nnoremap <C-L> <C-W><C-L>
nnoremap <C-H> <C-W><C-H>
noremap <F3> :Autoformat<CR><CR>
nnoremap <F5> <C-W>+
nnoremap <F6> <C-W>-
nnoremap <F7> <C-W>>
nnoremap <F8> <C-W><
nnoremap <F9> <C-W>=

set nocompatible              " be iMproved, required
filetype off                  " required

" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
" alternatively, pass a path where Vundle should install plugins
"call vundle#begin('~/some/path/here')

Plugin 'VundleVim/Vundle.vim'
Plugin 'Valloric/YouCompleteMe'
Plugin 'godlygeek/tabular'
Plugin 'plasticboy/vim-markdown'
Plugin 'airblade/vim-gitgutter'
Plugin 'mrtazz/DoxygenToolkit.vim'
Plugin 'Chiel92/vim-autoformat'
Plugin 'https://github.com/tpope/vim-commentary'
Plugin 'git://github.com/altercation/vim-colors-solarized.git'
Plugin 'bling/vim-airline'

" All of your Plugins must be added before the following line
call vundle#end()            " required
filetype plugin indent on    " required

" let g:ycm_global_ycm_extra_conf = "/vagrant/ycm_extra_conf.py"
" let g:ycm_confirm_extra_conf=0
" let g:ycm_autoclose_preview_window_after_insertion = 1
let g:DoxygenToolkit_briefTag_pre="@brief "
let g:DoxygenToolkit_paramTag_pre="@param "
let g:DoxygenToolkit_returnTag="@return "
let g:airline#extensions#tabline#enabled = 1
let g:airline_powerline_fonts = 1

