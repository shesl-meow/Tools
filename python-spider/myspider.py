# -*- coding: utf-8 -*-
"""
Created on Mon Jul 9 18:05:23 2018

@author: Allen

Modify on Sun Jul 15 15:30:00 2018

@author: shesl-meow
"""

import os
import urllib
import chardet
import re
from bs4 import BeautifulSoup
from lxml import etree
from urllib.parse import urljoin
from random import choice
from time import sleep
from selenium import webdriver

file_path=os.getcwd()
ban_word=re.compile(r"[/\*:：？?'<>|]")
coding_set='utf-8'


def empty_if_error(root,XPath):
    """
    定义函数，如果XPath指向的内容为空，返回空字符串；否则返回其list[0]

    参数：
    root lxml树的根节点；XPath通过root到目标的xpath
    """
    res = root.xpath(XPath+'/text()')
    if len(res) > 0:
        return "'" + res[0] + "'" # 由于sql的需要，将str用' wrap起来
    else:
        return "''"


def find_class_text_sep(root,*class_name):
    """
    class_name为多参数，找到所有class_name属性的文本并返回

    @shesl-meow:2018-7-15, 将名字由find_class_text修改为find_class_text_sep
    """
    string=''
    for name in class_name:
        elements=root.xpath("//*[@class='%s']"%name)
        for ele in elements: # 删去了if elements的非空判断 @shesl-meow
            string+=find_ele_down_text(ele)+'\n'
    return string

def find_class_href_p(root,class_name): # 佘崧林添加函数 @shesl-meow
    """
    class_name为多参数，找到所有class_name属性的节点，并返回内部的href和p
    """
    href_list = []
    p_list = []
    children = root.xpath("//*[@class='%s']"%class_name)
    for child in children:
        elements = child.xpath("//a[starts-with(@href,'http')]")
        for ele in elements:
            href_list.append(ele.xpath("./@href")[0])
            p_list.append(ele.xpath("./text()")[0])
    return href_list, p_list

def find_ele_up(ele,string):
    """
    递归查找同级及以上结构string属性，返回element元素
    """
    _path="//*[@%s]"%string
    eles=etree.ElementTree(ele).xpath(_path)
    if len(eles)==0:
        return find_ele_up(ele.getparent(),string)
    return eles[0]

def find_ele_down_text(element,flag=False):
    """
    通过element查找标签下所有文本，flag=1日期提前
    """
    title=""
    for ele in etree.ElementTree(element).xpath('//*'):
        if ele.tag=='p':
            title+='\n  '
        if ele.text:
            if title:
                title+=' '
            title+=ele.text
    pattern=re.compile(r"\d{4}-\d{2}-\d{2}")
    match=re.findall(pattern,title)
    if(match and flag):
        match=match[0]
        print(match)
        title=match+' '+title.replace(match,'')
    return title

def download_all_file(url,root,cur_path,update=False,*extens):
    """
    下载文件，url为当前域名，root为etree根，cur_path当前输出文件夹路径,*extens为后缀名包
    """
    _set_=set()
    for ele in root.xpath("//*[@href]"):
        ex='.'+ele.get('href').split('.')[-1]
        if ex in extens:
            _url=urljoin(url,ele.get('href'))
            name=find_ele_down_text(ele,True).strip()
            title=name
            name=re.sub(ban_word,'-',name)
            if ex not in name:
                name+=ex
            file_name=cur_path+'\\'+name
            if title and _url not in _set_ and (update or not os.path.exists(file_name)):
                try:
                    _set_.add(_url)
                    if('75d0f43f-6deb-4508-bdac-d5fe2bd67f5d.doc' not in _url):
                        urllib.request.urlretrieve(_url, file_name)
                        print(file_name+' Success!')
                        sleep(1)
                except Exception as e:
                    print(e,_url)
                    continue

def download_all_picture(url,root,cur_path,update=False,*extens):
    """
    下载图片，url为当前域名，root为etree根，cur_path当前输出文件夹路径,*extens为后缀名包
    """
    cnt=0
    for ele in root.xpath("//img[@src]"):
        ex='.'+ele.get('src').split('.')[-1]
        if ex in extens:
            cnt+=1
            name=('0' if cnt<10 else '') + str(cnt)+ex
            file_name=cur_path+'/'+name
            if update or not os.path.exists(file_name):
                try:
                    _url=urljoin(url,ele.get('src'))
                    if('75d0f43f-6deb-4508-bdac-d5fe2bd67f5d.doc' not in _url):
                        urllib.request.urlretrieve(_url, file_name)
                        print(file_name+' Success!')
                        sleep(1)
                except Exception as e:
                    print(e,_url)
                    continue

def find_title_by_date(url,root):
    """
    通过xxxx-xx-xx的日期形式查找新闻标题，返回一个字典数组[{'file_name','title','href'}]，分别代表文件夹名，文章标题，链接
    """
    pattern=re.compile(r"\d{4}-\d{2}-\d{2}")
    ban_word=re.compile(r"[/\*:：？?'<>|]")
    the_list=[]
    try:
        for ele in root.xpath('//*'):
            if ele.text:
                match=re.findall(pattern, ele.text)
                if(match):
                    the_dict={}
                    passage=find_ele_up(ele,'href')
                    passage_title=find_ele_down_text(passage,True).strip()
                    href=urljoin(url,passage.get('href'))
                    passage_title=re.sub(ban_word,'-',passage_title)
                    the_dict['file_name']=passage_title
                    the_dict['title']=re.sub(pattern,'',passage_title).strip()
                    the_dict['href']=href
                    the_list.append(the_dict)
        return the_list
    except Exception as e:
        print(e)


def myremove(mylist,*elements):
    try:
        hasmove=0
        for ele in elements:
            if ele in mylist:
                mylist.remove(ele)
                hasmove=1
        if hasmove:
            return True
        else:
            return False
    except Exception as e:
        print(e)

def myremovepart(file_list,*elements):
    for ele in elements:
        for index in range(len(file_list)):
            if ele in file_list[index]:
                file_list[index]=file_list[index].replace(ele,'')


def get_file_path(file_list):
    file_name=file_path
    for name in file_list:
        file_name+='/'+name
    file_name+='.html'
    return file_name

def had_html(url):
    """
    检测目标文件是否已经存在。

    返回值：
    Exists状态值(bool)，True时表示，传入的url文件已经被爬取过，存在文件中；
    url对应文件名(str)，返回一个绝对路径的文件名
    """
    file_list=url.split('/')
    myremove(file_list,'http:','https:')
    myremovepart(file_list,'.aspx','.shtml','.html.','.htm','.xml')
    while(myremove(file_list,'')):
        pass
    file_name=get_file_path(file_list)
    file_name = file_name.replace('?', '_qMark_')
    if os.path.exists(file_name):
        return True,file_name
    else:
        return False,file_name

def get_html(file_name):
    with open(file_name,'rb') as f:
        return f.read()

def write_html(file_name,url):
    pos=file_name.rindex('/')
    up_file=file_name[:pos]
    if not os.path.exists(up_file):
        os.makedirs(up_file)
    with open(file_name,'wb') as f:
        print(file_name, "has been written.")
        f.write(url)

"""
用于随机生成代理的代理列表
"""
USER_AGENTS = [
    "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; AcooBrowser; .NET CLR 1.1.4322; .NET CLR 2.0.50727)",
    "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.0; Acoo Browser; SLCC1; .NET CLR 2.0.50727; Media Center PC 5.0; .NET CLR 3.0.04506)",
    "Mozilla/4.0 (compatible; MSIE 7.0; AOL 9.5; AOLBuild 4337.35; Windows NT 5.1; .NET CLR 1.1.4322; .NET CLR 2.0.50727)",
    "Mozilla/5.0 (Windows; U; MSIE 9.0; Windows NT 9.0; en-US)",
    "Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; Win64; x64; Trident/5.0; .NET CLR 3.5.30729; .NET CLR 3.0.30729; .NET CLR 2.0.50727; Media Center PC 6.0)",
    "Mozilla/5.0 (compatible; MSIE 8.0; Windows NT 6.0; Trident/4.0; WOW64; Trident/4.0; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR 3.0.30729; .NET CLR 1.0.3705; .NET CLR 1.1.4322)",
    "Mozilla/4.0 (compatible; MSIE 7.0b; Windows NT 5.2; .NET CLR 1.1.4322; .NET CLR 2.0.50727; InfoPath.2; .NET CLR 3.0.04506.30)",
    "Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN) AppleWebKit/523.15 (KHTML, like Gecko, Safari/419.3) Arora/0.3 (Change: 287 c9dfb30)",
    "Mozilla/5.0 (X11; U; Linux; en-US) AppleWebKit/527+ (KHTML, like Gecko, Safari/419.3) Arora/0.6",
    "Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.2pre) Gecko/20070215 K-Ninja/2.1.1",
    "Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN; rv:1.9) Gecko/20080705 Firefox/3.0 Kapiko/3.0",
    "Mozilla/5.0 (X11; Linux i686; U;) Gecko/20070322 Kazehakase/0.4.5",
    "Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.9.0.8) Gecko Fedora/1.9.0.8-1.fc10 Kazehakase/0.5.6",
    "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/535.11 (KHTML, like Gecko) Chrome/17.0.963.56 Safari/535.11",
    "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_7_3) AppleWebKit/535.20 (KHTML, like Gecko) Chrome/19.0.1036.7 Safari/535.20",
    "Opera/9.80 (Macintosh; Intel Mac OS X 10.6.8; U; fr) Presto/2.9.168 Version/11.52",
]

def get_req(url):
    # @shesl-meow修改前代码：headers = {'User-Agent':'Mozilla/5.0 (Windows NT 6.1; WOW64; rv:23.0) Gecko/20100101 Firefox/23.0'}
    headers= {"User-Agent": choice(USER_AGENTS)}
    req=urllib.request.Request(url=url, headers=headers)
    html=urllib.request.urlopen(req).read()
    return html

def get_req_with_js(url,waitTime=3):
    """
    使用浏览器模拟网页获取html文件，得到加载了JavaScript之后的html文件

    参数：
    url，网页目标url。
    可选参数waitTime，默认值为5，即函数会等待浏览器加载js 5秒钟。
    @ shesl-meow 2018.8.1 19:31
    """
    driver=webdriver.Chrome()
    driver.get(url)
    sleep(waitTime) # 等待网页加载完成
    html=driver.page_source.encode(coding_set)
    driver.close()
    return html

def prepare(url,update=False,toshow=False,jsLoad=False):
    """
    一系列请求操作，如果有本地缓存则使用，否则在线获取。

    参数：
    update=True时更新，返回etree根节点;
    toshow=True时显示状态;
    jsLoad=True时加载JavaScript动态网页。
    """
    had,file_name=had_html(url)
    if had and not update:
        html=get_html(file_name)
        if toshow:
            print(file_name,"找到存储文件")
        if jsLoad:
            print("使用jsLoad选项，但Update选项为False")
    else:
        if toshow:
            print(url,"更新")
        if jsLoad:
            html=get_req_with_js(url)
        else:
            html=get_req(url)
        sleep(1)
        write_html(file_name,html)
    charset=chardet.detect(html)['encoding']
    html=html.decode(charset,errors='ignore')
    html=re.sub(r"<!--\w+-->",'',html)
    root=etree.HTML(html)
    return root

if __name__=='__main__':
    url='https://www.baidu.com'
    prepare(url)
