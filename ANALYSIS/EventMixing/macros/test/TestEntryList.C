void TestEntryList(const char *printOpt="",Int_t entriesInEL=1e4,UInt_t max=1e5) {

   TFile f("EntryList.root","recreate");


   TEntryList *el = new TEntryList("main","Main Entry List");
   Int_t level1 = 10;
   Int_t level2 = 15;
   Int_t level3 = 20;

   TEntryList *el1,*el2,*el3;
   Int_t i=0,j=0,k=0;
   for (i=0;i<level1;i++) {
      j=0;k=0;
      el1 = CreateEntryList(Form("_%d_%d_%d_1",i,j,k),entriesInEL,max);
      el1->SetTreeName("aodTree_1");
      el1->SetFileName(Form("file_%d_%d_%d.root",i,j,k));
      el->Add(el1);
      el1->Write();
      for (j=0;j<level2;j++) {
         el2 = CreateEntryList(Form("_%d_%d_%d_1",i,j,k),entriesInEL,max);
         el2->SetTreeName("aodTree_2");
         el2->SetFileName(Form("file_%d_%d_%d.root",i,j,k));
         el1->Add(el2);
         el2->Write();
         for (k=0;k<level3;k++) {
            el3 = CreateEntryList(Form("_%d_%d_%d_1",i,j,k),entriesInEL,max);
            el2->SetTreeName("aodTree_3");
            el2->SetFileName(Form("file_%d_%d_%d.root",i,j,k));
            el2->Add(el3);
            el3->Write();
         }
      }
   }
   //   el2->Print();

   //   el->Print();

   el->Write();
   f.Close();

   GetEntryListFromFile();
}

void GetEntryListFromFile() {
   TFile f("EntryList.root","read");
   TEntryList *el = (TEntryList*)f.Get("main");

   TEntryList *elOut1 = el->GetEntryList("aodTree_1","file_3_0_0.root");
   Printf("Name : %s",elOut1->GetName());
   elOut1->Print("");
   //   TEntryList *elOut2 = elOut1->GetEntryList("aodTree_2","file_3_3_0.root");
   //   TEntryList *elOut3 = elOut2->GetEntryList("aodTree_3","file_3_3_4.root");
   //   elOut3->Print("all");

}

TEntryList *CreateEntryList(const char*prefix="",Long64_t nEntries=100,UInt_t max=1) {
   TEntryList *el = new TEntryList(Form("name%s",prefix),Form("title%s",prefix));
   el->SetTree("aodTree",Form("file_%s.root",prefix));

   TRandom r;
   r.SetSeed();
   for (Long64_t i=0;i<nEntries;i++) {
      el->Enter(r.Integer(max));
   }
   return el;
}
