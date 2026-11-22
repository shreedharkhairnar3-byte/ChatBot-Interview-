const roleData = {
 cpp: {name:"C++ Developer", questions:[
  ["Tell me about yourself and why you are interested in C++ development.",["c++","programming","problem solving","project"],"Connect your skills to a project and explain what you want to learn."],
  ["What is the difference between a class and an object in C++?",["class","blueprint","object","instance"],"A class defines a structure; an object is an instance of that class."],
  ["What is the difference between a pointer and a reference?",["address","pointer","reference","null","alias"],"Mention addresses, null pointers, and references acting as aliases."],
  ["What is a constructor? Name two types of constructors.",["constructor","initialize","default","parameterized","copy"],"Describe when constructors run and give examples of constructor types."],
  ["Explain inheritance and one situation where it is useful.",["inheritance","base","derived","reuse","class"],"Give a simple base-class and derived-class example."],
  ["What is polymorphism in C++?",["polymorphism","overloading","overriding","virtual","runtime"],"Differentiate compile-time and runtime polymorphism."],
  ["What is the purpose of a virtual function?",["virtual","override","runtime","base","derived"],"Explain runtime method selection through a base-class pointer or reference."],
  ["What is the difference between stack and heap memory?",["stack","heap","automatic","dynamic","allocation"],"Discuss lifetime, allocation, and who manages the memory."],
  ["What is a destructor and when is it called?",["destructor","cleanup","release","object","scope"],"Mention resource cleanup when an object is destroyed."],
  ["How do you handle errors or exceptions in C++?",["try","catch","throw","exception","error"],"Give a small example using try, throw, and catch."]
 ]},
 fresher:{name:"General Fresher",questions:[
  ["Tell me about yourself.",["education","skills","project","goal","interest"],"Use a simple structure: education, skills, project, and career goal."],
  ["What are your strengths?",["communication","teamwork","learning","problem solving","adaptable"],"Support each strength with a short real example."],
  ["What is one skill you are currently improving?",["learning","practice","improve","feedback","goal"],"Explain the steps you are taking to improve."],
  ["Describe a project you have worked on.",["project","problem","solution","role","result"],"Explain the problem, your contribution, tools, and outcome."],
  ["How do you handle a difficult task?",["plan","break","research","ask","solution"],"Describe how you divide the task and check progress."],
  ["How do you work in a team?",["teamwork","communicate","listen","responsibility","support"],"Include an example of collaboration."],
  ["Why should we select you?",["skills","learn","contribute","dedicated","team"],"Connect your abilities with your willingness to learn."],
  ["Where do you see yourself in five years?",["career","skills","experience","growth","goal"],"Give a realistic answer focused on learning and responsibility."],
  ["How do you manage deadlines?",["prioritize","plan","time","deadline","progress"],"Mention prioritization, milestones, and communicating early."],
  ["Do you have any questions for the interviewer?",["role","team","expectations","learning","company"],"Ask about the role, team, learning opportunities, or expectations."]
 ]},
 python:{name:"Python Developer",questions:[
  ["What are the main features of Python?",["readable","interpreted","dynamic","library","high level"],"Mention readability, interpreted execution, and its ecosystem."],
  ["What is the difference between a list and a tuple?",["list","tuple","mutable","immutable"],"Focus on whether elements can be changed after creation."],
  ["What is a dictionary in Python?",["key","value","mapping","unique"],"Explain key-value pairs and show a simple use case."],
  ["What is the purpose of a function?",["def","reuse","parameter","return","task"],"Explain reusable blocks of code, inputs, and return values."],
  ["What is object-oriented programming?",["class","object","encapsulation","inheritance","polymorphism"],"Describe classes and objects, then mention core OOP concepts."],
  ["What is exception handling in Python?",["try","except","finally","exception","error"],"Explain how try and except handle errors."],
  ["What is the difference between == and is?",["value","identity","equal","same object"],"Explain value equality versus object identity."],
  ["What is a module?",["module","file","import","reuse","function"],"Describe a Python file that can be imported."],
  ["What is a virtual environment?",["environment","dependencies","packages","isolated"],"Explain isolated project dependencies."],
  ["How would you debug a Python program?",["debug","error","print","breakpoint","traceback"],"Mention reading tracebacks, reproducing bugs, and using breakpoints."]
 ]}
};
const $=id=>document.getElementById(id);
let role=null,index=0,answers=[],sessionName="",lastReport=null;
function show(view){["homeView","chatView","resultView","historyView"].forEach(id=>$(id).classList.toggle("hidden",id!==view));$("crumb").textContent=view==="homeView"?"Practice":view==="historyView"?"My sessions":view==="chatView"?"Interview":"Results";window.scrollTo(0,0)}
function toast(msg){$("toast").textContent=msg;$("toast").classList.add("show");setTimeout(()=>$("toast").classList.remove("show"),2300)}
function addMessage(text,type="bot"){let el=document.createElement("div");el.className="message "+(type==="user"?"user":"");if(type==="bot"){let av=document.createElement("div");av.className="bot-avatar";av.textContent="✦";el.append(av)}let b=document.createElement("div");b.className="bubble";b.textContent=text;el.append(b);$("messages").append(el);$("messages").scrollTop=$("messages").scrollHeight}
function start(key){role=roleData[key];index=0;answers=[];sessionName=role.name;$("chatRoleTitle").textContent=role.name;$("messages").innerHTML="";show("chatView");addMessage("Hello! Welcome to your "+role.name+" mock interview. I’ll ask 10 questions. Take your time, and try to include examples. Ready? Let’s begin!");ask()}
function ask(){let q=role.questions[index];$("progressLabel").textContent=`Question ${index+1} of 10`;$("progressPercent").textContent=`${(index+1)*10}%`;$("progressBar").style.width=((index+1)*10)+"%";$("coachTip").textContent=q[2];addMessage(q[0]);$("answerInput").value="";$("answerInput").focus()}
function scoreAnswer(answer,keywords){let a=answer.toLowerCase(),matched=keywords.filter(k=>a.includes(k.toLowerCase()));let score=answer.trim()?Math.min(10,2+matched.length*2+(answer.length>=80?2:0)+(answer.length>=180?1:0)):0;return {score,matched}}
function submitAnswer(skip=false){let answer=skip?"[Skipped]":$("answerInput").value.trim();if(!skip&&!answer){toast("Write an answer or choose skip.");return}let q=role.questions[index],result=skip?{score:0,matched:[]}:scoreAnswer(answer,q[1]);if(!skip)addMessage(answer,"user");else addMessage("I’ll skip this one and move on.","user");answers.push({question:q[0],answer,tip:q[2],score:result.score,matched:result.matched});if(skip)addMessage("No problem. Let’s move to the next question.");else if(result.score>=8)addMessage("Good response! You covered several important points. Practice score: "+result.score+"/10.");else if(result.score>=5)addMessage("Nice attempt. Add more relevant details and an example. Practice score: "+result.score+"/10.");else addMessage("Keep practising. Try to include key concepts and a clear example. Practice score: "+result.score+"/10.");index++;if(index<10){setTimeout(ask,350)}else setTimeout(showResults,450)}
function showResults(){let total=answers.reduce((s,a)=>s+a.score,0),percent=total;let matched=answers.reduce((s,a)=>s+a.matched.length,0),count=answers.filter(a=>a.answer!=="[Skipped]").length;$("scoreValue").textContent=percent;$("scoreRing").style.background=`conic-gradient(#819678 ${percent*3.6}deg,#edf0e9 0deg)`;$("answeredCount").textContent=count+"/10";$("matchedCount").textContent=matched;$("resultMessage").textContent=percent>=80?"Excellent practice!":percent>=60?"Good progress!":percent>=40?"Keep building your skills!":"Every practice counts!";$("resultDescription").textContent=percent>=70?"You’re building a solid foundation. Review the pointers below to polish your answers.":"Review the suggestions below, practise the fundamentals, and give it another try.";let list=$("reviewList");list.innerHTML="";answers.forEach((a,i)=>{let item=document.createElement("article");item.className="review-item";let head=document.createElement("div");head.className="review-head";let title=document.createElement("b");title.textContent=`Q${i+1}. ${a.question}`;let mark=document.createElement("span");mark.textContent=a.score+"/10";head.append(title,mark);let ans=document.createElement("p");ans.className="your-answer";ans.textContent="Your answer: "+a.answer;let tip=document.createElement("p");tip.textContent="Suggestion: "+a.tip;item.append(head,ans,tip);list.append(item)});lastReport={date:new Date().toLocaleString(),role:role.name,total,answers};let sessions=JSON.parse(localStorage.getItem("im_sessions")||"[]");sessions.unshift({date:lastReport.date,role:role.name,total});localStorage.setItem("im_sessions",JSON.stringify(sessions.slice(0,20)));show("resultView")}
function downloadReport(){if(!lastReport)return;let lines=["INTERVIEW MATE — PRACTICE REPORT","================================",`Date: ${lastReport.date}`,`Category: ${lastReport.role}`,`Total score: ${lastReport.total}/100`,"","ANSWER REVIEW"];lastReport.answers.forEach((a,i)=>lines.push("",`Q${i+1}: ${a.question}`,`Answer: ${a.answer}`,`Score: ${a.score}/10`,`Concepts spotted: ${a.matched.join(", ")||"None detected"}`,`Suggestion: ${a.tip}`));lines.push("","Note: This is a simple keyword-based practice estimate, not an AI assessment.");let blob=new Blob([lines.join("\n")],{type:"text/plain"}),url=URL.createObjectURL(blob),a=document.createElement("a");a.href=url;a.download="interview-mate-report.txt";a.click();URL.revokeObjectURL(url)}
function showHistory(){let sessions=JSON.parse(localStorage.getItem("im_sessions")||"[]"),list=$("historyList");list.innerHTML="";if(!sessions.length){list.innerHTML='<div class="history-row">No sessions yet. Start your first practice interview!</div>'}else sessions.forEach(s=>{let row=document.createElement("div");row.className="history-row";let left=document.createElement("div");left.innerHTML=`<b>${s.role}</b><small>${s.date}</small>`;let right=document.createElement("div");right.className="history-score";right.textContent=s.total+"/100";row.append(left,right);list.append(row)});show("historyView")}
document.querySelectorAll(".role-card").forEach(btn=>btn.addEventListener("click",()=>start(btn.dataset.role)));
$("answerForm").addEventListener("submit",e=>{e.preventDefault();submitAnswer(false)});
$("answerInput").addEventListener("keydown",e=>{if(e.key==="Enter"&&(e.ctrlKey||e.metaKey)){e.preventDefault();submitAnswer(false)}});
$("skipBtn").addEventListener("click",()=>submitAnswer(true));
$("backHome").addEventListener("click",()=>{if(confirm("Leave this session? Your current answers will not be saved."))show("homeView")});
$("navPractice").addEventListener("click",()=>show("homeView"));
$("navHistory").addEventListener("click",showHistory);
$("historyPractice").addEventListener("click",()=>show("homeView"));
$("newSessionBtn").addEventListener("click",()=>show("homeView"));
$("downloadBtn").addEventListener("click",downloadReport);
$("helpBtn").addEventListener("click",()=>toast("Choose a track, answer each question, and download your report at the end."));
